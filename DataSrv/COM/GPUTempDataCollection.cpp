// GPUTempDataCollection.cpp : Implementation of CGPUTempDataCollection

#include "pch.h"
#include <array>

#include "../DataSrv.h"
#include "../Utilities/ComUtilities.h"
#include "../Utilities/RangeUtilities.h"
#include "../Utilities/TypeUtilities.h"

#include "GPUTempData.h"
#include "GPUTempDataCollection.h"


// Construction

CGPUTempDataCollection::CGPUTempDataCollection()
{
}

HRESULT CGPUTempDataCollection::FinalConstruct()
{
	return S_OK;
}

void CGPUTempDataCollection::FinalRelease()
{
}

// Methods

STDMETHODIMP CGPUTempDataCollection::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const auto arr = std::to_array({ IID_IGPUTempDataCollection });

    const auto res = CComUtilities::HasInterface(arr, riid);
    return res ? S_OK : S_FALSE;
}

STDMETHODIMP CGPUTempDataCollection::get__NewEnum(IUnknown** ppUnk)
{
    if (ppUnk == nullptr)
    {
        return CComUtilities::ErrorInvalidPointer(this, IID_IGPUTempDataCollection);
    }

    ObjectLock lock(this);

    return TCollectionImpl::get__NewEnum(ppUnk);
}

STDMETHODIMP CGPUTempDataCollection::get_Item(long index, IGPUTempData** ppGPUTempData)
{
    if (ppGPUTempData == nullptr)
    {
        return CComUtilities::ErrorInvalidPointer(this, IID_IGPUTempDataCollection);
    }

    ObjectLock lock(this);

    const auto adapterCount = GetProvider().GetAdapterCount();
    if (adapterCount == 0 ||
       !CRangeUtilities::IsBetween(index, 1L, static_cast<long>(adapterCount)))
    {
        return CComUtilities::ErrorInvalidPointer(this, IID_IGPUTempDataCollection);
    }

    const auto adapterIndex = CTypeUtilities::type_of(adapterCount, index - 1);
    const auto hr = CComUtilities::CreateCom<CGPUTempData>(ppGPUTempData, [&](auto pGpuTempData)
    {
        return pGpuTempData->Init(adapterIndex);
    });

    return hr;
}

STDMETHODIMP CGPUTempDataCollection::get_Count(long* pVal)
{
    if (pVal == nullptr)
    {
        return CComUtilities::ErrorInvalidPointer(this, IID_IGPUTempDataCollection);
    }

    ObjectLock lock(this);

    const auto adapterCount = GetProvider().GetAdapterCount();
    *pVal = static_cast<long>(adapterCount);

    return S_OK;
}

// Helper Methods

CGPUTempDataCollection::TDataProvider& CGPUTempDataCollection::GetProvider()
{
    return CDataSrvModule::GetModule().GetGPUTempProvide();
}
