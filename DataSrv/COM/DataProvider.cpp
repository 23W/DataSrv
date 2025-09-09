// DataProvider.cpp : Implementation of CDataProvider

#include "pch.h"
#include "DataProvider.h"


// CDataProvider

STDMETHODIMP CDataProvider::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* const arr[] = 
	{
		&IID_IDataProvider
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
