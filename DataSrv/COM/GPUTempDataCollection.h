// GPUTempDataCollection.h : Declaration of the CGPUTempDataCollection

#pragma once
#include "resource.h"       // main symbols

#include "../DataSrv.h"
#include "../Utilities/ComCollectionImpl.h"


using namespace ATL;


// CGPUTempDataCollection

class ATL_NO_VTABLE CGPUTempDataCollection :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CGPUTempDataCollection, &CLSID_GPUTempDataCollection>,
    public ISupportErrorInfo,
    public IDispatchImpl<IGPUTempDataCollection, &IID_IGPUTempDataCollection, &LIBID_DataSrvLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    private CComDispCollectionImpl<IGPUTempData, CComMultiThreadModel>
{
public:
    using TDataProvider = CDataSrvModule::TGpuTemp;
    using TCollectionImpl = CComDispCollectionImpl<IGPUTempData, CComMultiThreadModel>;

    // Construction

    CGPUTempDataCollection();

    HRESULT FinalConstruct();
    void FinalRelease();

    DECLARE_REGISTRY_RESOURCEID(IDR_GPUTEMPDATACOLLECTION)
    DECLARE_NOT_AGGREGATABLE(CGPUTempDataCollection)
    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CGPUTempDataCollection)
        COM_INTERFACE_ENTRY(IGPUTempDataCollection)
        COM_INTERFACE_ENTRY(IDispatch)
        COM_INTERFACE_ENTRY(ISupportErrorInfo)
    END_COM_MAP()

    // Methods

    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
    STDMETHOD(get__NewEnum)(IUnknown** ppUnk) override;
    STDMETHOD(get_Item)(long index, IGPUTempData** ppGPUTempData) override;
    STDMETHOD(get_Count)(long* pVal) override;

private:

    // Helper Methods

    TDataProvider& GetProvider();
};

OBJECT_ENTRY_AUTO(__uuidof(GPUTempDataCollection), CGPUTempDataCollection)
