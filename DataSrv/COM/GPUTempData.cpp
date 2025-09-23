// GPUTempData.cpp : Implementation of CGPUTempData

#include "pch.h"

#include "../DataSrv.h"
#include "../Utilities/ComUtilities.h"

#include "GPUTempData.h"


// Construction

CGPUTempData::CGPUTempData()
{
}

HRESULT CGPUTempData::FinalConstruct()
{
    return S_OK;
}

void CGPUTempData::FinalRelease()
{
}

// Methods

STDMETHODIMP CGPUTempData::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const std::array<IID, 1> arr =
    {
        IID_IGPUTempData
    };

    const auto res = CComUtilities::HasInterface(arr, riid);
    return res ? S_OK : S_FALSE;
}
