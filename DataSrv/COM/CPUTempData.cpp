// CPUTempData.cpp : Implementation of CCPUTempData

#include "pch.h"
#include "CPUTempData.h"


// CCPUTempData

STDMETHODIMP CCPUTempData::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_ICPUTempData
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
