#include "pch.h"
#include <array>
#include <dxcore.h>
#include <dxcore_interface.h>

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

            for (auto index = util::type_of_cv(count, 0); index < count; index++)
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
