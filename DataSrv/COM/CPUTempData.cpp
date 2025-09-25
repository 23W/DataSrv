// CPUTempData.cpp : Implementation of CCPUTempData

#include "pch.h"

#include "../DataSrv.h"
#include "../Utilities/ComUtilities.h"
#include "../Utilities/RangeUtilities.h"

#include "CPUTempData.h"


// Construction

CCPUTempData::CCPUTempData() 
    : m_eventId(0)
    , m_sourceType(SourceType::PDH)
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

STDMETHODIMP CCPUTempData::get_Source(SourceType* pSourceType)
{
    if (pSourceType == nullptr)
    {
        return CComUtilities::ErrorInvalidPointer(this, IID_IDataProvider);
    }

    *pSourceType = m_sourceType;
    return S_OK;
}

STDMETHODIMP CCPUTempData::put_Source(SourceType sourceType)
{
    if (!CRangeUtilities::IsBetween(sourceType, SourceType::_Min, SourceType::_Max))
    {
        return CComUtilities::ErrorInvalidPointer(this, IID_IDataProvider);
    }

    ObjectLock lock(this);

    ChangeSourceType(sourceType);
    return S_OK;
}

// Helper Methods

CCPUTempData::TDataProvider& CCPUTempData::GetProvider()
{
    return CDataSrvModule::GetModule().GetCPUTempProvide(m_sourceType);
}

void CCPUTempData::ChangeSourceType(SourceType sourceType)
{
    if (sourceType != m_sourceType)
    {
        UnsubscribeDataEvent();

        m_sourceType = sourceType;

        SubscribeDataEvent();
    }
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

// Event handlers

void CCPUTempData::OnNextSample(float value)
{
    Fire_OnNextSample(value);
}
