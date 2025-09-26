// DataProvider.cpp : Implementation of CDataProvider

#include "pch.h"
#include <array>

#include "../DataSrv.h"
#include "../Utilities/ComUtilities.h"

#include "CPUTempData.h"
#include "GPUTempDataCollection.h"
#include "DataProvider.h"


// Construction

CDataProvider::CDataProvider()
{
}

HRESULT CDataProvider::FinalConstruct()
{
    return S_OK;
}

void CDataProvider::FinalRelease()
{
}

// Methods

STDMETHODIMP CDataProvider::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const auto arr = std::to_array({ IID_IDataProvider });

    const auto res = CComUtilities::HasInterface(arr, riid);
    return res ? S_OK : S_FALSE;
}

STDMETHODIMP CDataProvider::get_CpuTemp(ICPUTempData** ppProvider)
{
    if (ppProvider == nullptr)
    {
        return CComUtilities::ErrorInvalidPointer(this, IID_IDataProvider);
    }

    ObjectLock lock(this);

    const auto hr = CComUtilities::CreateCOM<CCPUTempData>(ppProvider);
    return hr;
}

STDMETHODIMP CDataProvider::get_GpuTemp(IGPUTempDataCollection** ppCollectionProvider)
{
    if (ppCollectionProvider == nullptr)
    {
        return CComUtilities::ErrorInvalidPointer(this, IID_IDataProvider);
    }

    ObjectLock lock(this);

    const auto hr = CComUtilities::CreateCOM<CGPUTempDataCollection>(ppCollectionProvider);
    return hr;
}