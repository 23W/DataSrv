// CPUTempData.h : Declaration of the CCPUTempData

#pragma once
#include "../resource.h"       // main symbols

#include "../DataSrv.h"
#include "_ICPUTempDataEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


class ATL_NO_VTABLE CCPUTempData :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CCPUTempData, &CLSID_CPUTempData>,
    public ISupportErrorInfo,
    public IConnectionPointContainerImpl<CCPUTempData>,
    public CProxy_ICPUTempDataEvents<CCPUTempData>,
    public IDispatchImpl<ICPUTempData, &IID_ICPUTempData, &LIBID_DataSrvLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
    using TDataProvider = CDataSrvModule::TCpuTemp;
    using TEventHandlerId = TDataProvider::TId;

    // Construction

    CCPUTempData();

    HRESULT FinalConstruct();
    void FinalRelease();

    DECLARE_REGISTRY_RESOURCEID(IDR_CPUTEMPDATA)
    DECLARE_NOT_AGGREGATABLE(CCPUTempData)
    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CCPUTempData)
        COM_INTERFACE_ENTRY(ICPUTempData)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
        COM_INTERFACE_ENTRY(IConnectionPointContainer)
    END_COM_MAP()

    BEGIN_CONNECTION_POINT_MAP(CCPUTempData)
        CONNECTION_POINT_ENTRY(__uuidof(_ICPUTempDataEvents))
    END_CONNECTION_POINT_MAP()

    // Methods

    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

    STDMETHOD(get_Source)(SourceType* pSourceType);
    STDMETHOD(put_Source)(SourceType sourceType);

private:

    // Helper Methods

    TDataProvider& GetProvider();

    void ChangeSourceType(SourceType sourceType);

    void SubscribeDataEvent();
    void UnsubscribeDataEvent();

    // Event handlers

    void OnNextSample(float sample);

    // Members

    TEventHandlerId m_eventId;
    SourceType m_sourceType;
};

OBJECT_ENTRY_AUTO(__uuidof(CPUTempData), CCPUTempData)
