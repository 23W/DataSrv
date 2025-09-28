#include "pch.h"
#include <array>
#include <dxcore.h>
#include <dxcore_interface.h>

#include "../DataSrv.h"
#include "../Utilities/StringUtilities.h"
#include "../Utilities/TypeUtilities.h"
#include "GPUTempProvider.h"

#pragma comment(lib, "dxcore.lib")
#pragma comment(lib, "dxguid.lib")

// ----------------------------------------------------------------------------
// CGPUTempProvider::CAdapter

// Construction

CGPUTempProvider::CAdapter::CAdapter(ATL::CComPtr<IDXCoreAdapter>&& spAdapter) noexcept
    : m_spAdapter(std::move(spAdapter))
{
    ATLASSERT(!!m_spAdapter);
}

CGPUTempProvider::CAdapter::CAdapter(CAdapter&& adapter) noexcept
    : m_spAdapter(std::move(adapter.m_spAdapter))
{
}

CGPUTempProvider::CAdapter::~CAdapter()
{
}

CGPUTempProvider::CAdapter& CGPUTempProvider::CAdapter::operator = (CAdapter&& adapter) noexcept
{
    m_spAdapter.Attach(adapter.m_spAdapter.Detach());
    return *this;
}

ATL::CStringW CGPUTempProvider::CAdapter::GetDescription()
{
    std::unique_lock<TLock> lock;

    auto res = ATL::CStringW{};

    if (m_spAdapter->IsPropertySupported(DXCoreAdapterProperty::DriverDescription))
    {
        auto description = std::array<char, 2048>{ '\0' };
        if (SUCCEEDED(m_spAdapter->GetProperty(DXCoreAdapterProperty::DriverDescription,
                                              (description.size() - 1) * sizeof(char),
                                               description.data())))
        {
            res = CStringUtilities::Utf8ToCString(description.data(),
                                                  std::strlen(description.data()));
        }
    }

    return res;
}

size_t CGPUTempProvider::CAdapter::GetPhysicalCount()
{
    std::unique_lock<TLock> lock;

    auto res = size_t{ 1 };

    if (m_spAdapter->IsPropertySupported(DXCoreAdapterProperty::PhysicalAdapterCount))
    {
        auto count = uint32_t{};
        if (SUCCEEDED(m_spAdapter->GetProperty(DXCoreAdapterProperty::PhysicalAdapterCount, &count)))
        {
            res = count;
        }
    }

    return res;
}

float CGPUTempProvider::CAdapter::GetTemp(size_t physicalIndex)
{
    std::unique_lock<TLock> lock;

    auto res = 0.f;

    auto index = static_cast<uint32_t>(physicalIndex);
    if (FAILED(m_spAdapter->QueryState(DXCoreAdapterState::AdapterTemperatureCelsius, &index, &res)))
    {
        res = 0.f;
    }

    return res;
}

float CGPUTempProvider::CAdapter::GetAvgTemp()
{
    std::unique_lock<TLock> lock;

    auto res = 0.f;
    auto delim = 0;

    for (auto count = GetPhysicalCount(), index = CTypeUtilities::type_of(count, 0); index < count; index++)
    {
        const auto temp = GetTemp(index);
        if (temp != 0)
        {
            res += temp;
            delim++;
        }
    }

    res /= delim;
    return res;
}

void CGPUTempProvider::CAdapter::RunThread()
{
    if (m_threadRunning)
    {
        return;
    }

    m_thread = std::thread([this]()
    {
        CDataSrvModule::InitializeCom();

        std::unique_lock<TLock> lock(m_lock);
        m_threadRunning = true;

        while (m_threadRunning)
        {
            const auto celsius = GetAvgTemp();

            lock.unlock();
            m_event.Notify(celsius);
            lock.lock();

            m_threadWakeup.wait_for(lock, std::chrono::milliseconds(500), [this]() { return !m_threadRunning; });
        }
    });
}

// CGPUTempProvider::CAdapter
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// CAdapter

// Construction

CGPUTempProvider::CGPUTempProvider()
    : m_initialized(false)
{
}

CGPUTempProvider::~CGPUTempProvider()
{
}

// Methods

// Helper Methods

void CGPUTempProvider::Init()
{
    if (m_initialized)
    {
        return;
    }

    m_initialized = true;

    ATL::CComPtr<IDXCoreAdapterFactory> spFactory;
    if (SUCCEEDED(DXCoreCreateAdapterFactory(&spFactory)))
    {
        ATL::CComPtr<IDXCoreAdapterList> spAdapterList;
        const auto dxguid = DXCORE_ADAPTER_ATTRIBUTE_D3D12_CORE_COMPUTE; // DXCORE_ADAPTER_ATTRIBUTE_D3D11_GRAPHICS
        if (SUCCEEDED(spFactory->CreateAdapterList(1, &dxguid, &spAdapterList)))
        {
            static const auto sortPreferences = std::to_array(
            {
                DXCoreAdapterPreference::Hardware,
                DXCoreAdapterPreference::HighPerformance
            });
            spAdapterList->Sort(static_cast<uint32_t>(sortPreferences.size()),
                                sortPreferences.data());

            const auto count = spAdapterList->GetAdapterCount();
            m_adapters.reserve(count);

            for (auto index = CTypeUtilities::type_of_cv(count, 0); index < count; index++)
            {
                ATL::CComPtr<IDXCoreAdapter> spAdapter;
                if (SUCCEEDED(spAdapterList->GetAdapter(index, &spAdapter)))
                {
                    auto isHardware = false;
                    spAdapter->GetProperty(DXCoreAdapterProperty::IsHardware, &isHardware);
                    if (isHardware)
                    {
                        m_adapters.emplace_back(std::move(spAdapter));
                    }
                }
            }
        }
    }
}

// CAdapter
// ----------------------------------------------------------------------------
