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
    using TDataProvider = CDataSrvModule::TGpuTemp;
    using TAdapterProvider = TDataProvider::CAdapter;
    using TEventHandlerId = TAdapterProvider::TId;

    // Construction

    CGPUTempData();

    HRESULT FinalConstruct();
    void FinalRelease();

    HRESULT Init(size_t adapterIndex);

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

    STDMETHOD(get_Index)(long* pIndex);
    STDMETHOD(get_Name)(BSTR* ppName);

private:

    // Helper Methods

    bool IsValid();

    TDataProvider& GetProvider();

    void SubscribeDataEvent();
    void UnsubscribeDataEvent();

    // Event handlers

    void OnNextSample(float sample);

    // Members

    TEventHandlerId m_eventId;
    size_t m_adapterIndex;
};

OBJECT_ENTRY_AUTO(__uuidof(GPUTempData), CGPUTempData)
