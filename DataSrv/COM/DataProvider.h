// DataProvider.h : Declaration of the CDataProvider

#pragma once
#include "../resource.h"       // main symbols

#include "DataSrv_i.h"
#include "_IDataProviderEvents_CP.h"


using namespace ATL;

// CDataProvider

class ATL_NO_VTABLE CDataProvider :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CDataProvider, &CLSID_DataProvider>,
    public ISupportErrorInfo,
    public IConnectionPointContainerImpl<CDataProvider>,
    public CProxy_IDataProviderEvents<CDataProvider>,
    public IDispatchImpl<IDataProvider, &IID_IDataProvider, &LIBID_DataSrvLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
    CDataProvider()
    {
    }

    DECLARE_REGISTRY_RESOURCEID(IDR_DATAPROVIDER)
    DECLARE_NOT_AGGREGATABLE(CDataProvider)

    BEGIN_COM_MAP(CDataProvider)
        COM_INTERFACE_ENTRY(IDataProvider)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
        COM_INTERFACE_ENTRY(IConnectionPointContainer)
    END_COM_MAP()

    BEGIN_CONNECTION_POINT_MAP(CDataProvider)
        CONNECTION_POINT_ENTRY(__uuidof(_IDataProviderEvents))
    END_CONNECTION_POINT_MAP()

    // ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);


    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease()
    {
    }

public:
};

OBJECT_ENTRY_AUTO(__uuidof(DataProvider), CDataProvider)
