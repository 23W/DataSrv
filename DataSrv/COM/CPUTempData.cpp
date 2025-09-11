// CPUTempData.cpp : Implementation of CCPUTempData

#include "pch.h"

#include "../DataSrv.h"
#include "../Utilities/ComUtilities.h"

#include "CPUTempData.h"


// Construction

CCPUTempData::CCPUTempData() 
    : m_eventId(0)
{}

HRESULT CCPUTempData::FinalConstruct()
{
    SubscribeDataEvent();
    return S_OK;
}

void CCPUTempData::FinalRelease()
{
    UnsubscribeDataEvent();
}

// Methods

STDMETHODIMP CCPUTempData::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const std::array<IID, 1> arr =
    {
        IID_ICPUTempData
    };

    const auto res = CComUtilities::HasInterface(arr, riid);
    return res ? S_OK : S_FALSE;
}

// Helper Methods

CCPUTempData::TDataProvider& CCPUTempData::GetProvider()
{
    return CDataSrvModule::GetModule().GetCPUTempProvide();
}

void CCPUTempData::SubscribeDataEvent()
{
    m_eventId = GetProvider().Subscrive([this](float value) { OnNextSample(value); });
}

void CCPUTempData::UnsubscribeDataEvent()
{
    if (m_eventId != 0)
    {
        GetProvider().Unsubscrive(m_eventId);
        m_eventId = 0;
    }
}

void CCPUTempData::OnNextSample(float value)
{
    Fire_OnNextSample(value);
}
