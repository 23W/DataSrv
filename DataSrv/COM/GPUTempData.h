// GPUTempData.h : Declaration of the CGPUTempData

#pragma once
#include "../resource.h"       // main symbols

#include "../DataSrv.h"
#include "_IGPUTempDataEvents_CP.h"



using namespace ATL;


// CGPUTempData

class ATL_NO_VTABLE CGPUTempData :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CGPUTempData, &CLSID_GPUTempData>,
    public ISupportErrorInfo,
    public IConnectionPointContainerImpl<CGPUTempData>,
    public CProxy_IGPUTempDataEvents<CGPUTempData>,
    public IDispatchImpl<IGPUTempData, &IID_IGPUTempData, &LIBID_DataSrvLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:

    // Construction

    CGPUTempData();

    HRESULT FinalConstruct();

    void FinalRelease();


    DECLARE_REGISTRY_RESOURCEID(IDR_GPUTEMPDATA)
    DECLARE_NOT_AGGREGATABLE(CGPUTempData)
    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CGPUTempData)
        COM_INTERFACE_ENTRY(IGPUTempData)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
        COM_INTERFACE_ENTRY(IConnectionPointContainer)
    END_COM_MAP()

    BEGIN_CONNECTION_POINT_MAP(CGPUTempData)
        CONNECTION_POINT_ENTRY(__uuidof(_IGPUTempDataEvents))
    END_CONNECTION_POINT_MAP()

    // Methods

    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

private:
};

OBJECT_ENTRY_AUTO(__uuidof(GPUTempData), CGPUTempData)
