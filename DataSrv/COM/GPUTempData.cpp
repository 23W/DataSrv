// GPUTempData.cpp : Implementation of CGPUTempData

#include "pch.h"
#include <array>

#include "../DataSrv.h"
#include "../Utilities/ComUtilities.h"
#include "../Utilities/RangeUtilities.h"
#include "../Utilities/TypeUtilities.h"

#include "GPUTempData.h"


// Construction

CGPUTempData::CGPUTempData()
    : m_eventId(0)
    , m_adapterIndex(0)
{
}

HRESULT CGPUTempData::FinalConstruct()
{
    return S_OK;
}

void CGPUTempData::FinalRelease()
{
    UnsubscribeDataEvent();
}

HRESULT CGPUTempData::Init(size_t adapterIndex)
{
    m_adapterIndex = adapterIndex;

    const auto hr = IsValid() ? S_OK : CComUtilities::ErrorInvalidIndex(this, IID_IGPUTempData);
    if (SUCCEEDED(hr))
    {
        SubscribeDataEvent();
    }

    return hr;
}

// Methods

STDMETHODIMP CGPUTempData::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const auto arr = std::to_array({ IID_IGPUTempData });

    const auto res = CComUtilities::HasInterface(arr, riid);
    return res ? S_OK : S_FALSE;
}

STDMETHODIMP CGPUTempData::get_Index(long* pIndex)
{
    if (pIndex == nullptr)
    {
        return CComUtilities::ErrorInvalidPointer(this, IID_IGPUTempData);
    }

    ObjectLock lock(this);

    if (!IsValid())
    {
        return CComUtilities::ErrorInvalidIndex(this, IID_IGPUTempData);
    }

    *pIndex = static_cast<long>(m_adapterIndex);
    return S_OK;
}

STDMETHODIMP CGPUTempData::get_Name(BSTR* ppName)
{
    if (ppName == nullptr)
    {
        return CComUtilities::ErrorInvalidPointer(this, IID_IGPUTempData);
    }

    ObjectLock lock(this);

    if (!IsValid())
    {
        return CComUtilities::ErrorInvalidIndex(this, IID_IGPUTempData);
    }

    auto& adapter = GetProvider().GetAdapter(m_adapterIndex);
    const auto desc = adapter.GetDescription();

    *ppName = CComBSTR(desc).Detach();
    return S_OK;
}

// Helper Methods

bool CGPUTempData::IsValid()
{
    return CRangeUtilities::IsBetween(m_adapterIndex,
                                      CTypeUtilities::type_of(m_adapterIndex, 0),
                                      GetProvider().GetAdapterCount());
}

CGPUTempData::TDataProvider& CGPUTempData::GetProvider()
{
    return CDataSrvModule::GetModule().GetGPUTempProvide();
}

void CGPUTempData::SubscribeDataEvent()
{
    if (m_eventId == 0)
    {
        auto& adapter = GetProvider().GetAdapter(m_adapterIndex);
        m_eventId = adapter.Subscrive([this](auto sample)
                                      {
                                          OnNextSample(sample);
                                      });
    }
}

void CGPUTempData::UnsubscribeDataEvent()
{
    if (m_eventId != 0)
    {
        auto& adapter = GetProvider().GetAdapter(m_adapterIndex);
        adapter.Unsubscrive(m_eventId);

        m_eventId = 0;
    }
}

// Event handlers

void CGPUTempData::OnNextSample(float sample)
{
    Fire_OnNextSample(sample);
}
