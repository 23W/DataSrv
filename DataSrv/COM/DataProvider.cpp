// DataProvider.cpp : Implementation of CDataProvider

#include "pch.h"

#include "../DataSrv.h"
#include "../Utilities/ComUtilities.h"

#include "CPUTempData.h"
#include "DataProvider.h"


STDMETHODIMP CDataProvider::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const std::array<IID, 1> arr =
    {
        IID_IDataProvider
    };

    const auto res = CComUtilities::HasInterface(arr, riid);
    return res ? S_OK : S_FALSE;
}

STDMETHODIMP CDataProvider::get_CpuTemp(ICPUTempData** ppData)
{
    if (ppData == nullptr)
    {
        return CComUtilities::ErrorInvalidPointer(this, IID_IDataProvider);
    }

    ObjectLock lock(this);

    const auto hr = CComUtilities::CreateCOM<CCPUTempData>(ppData);
    return hr;
}
