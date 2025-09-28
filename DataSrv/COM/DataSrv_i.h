

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 05:14:07 2038
 */
/* Compiler settings for COM\DataSrv.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DataSrv_i_h__
#define __DataSrv_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IDataProvider_FWD_DEFINED__
#define __IDataProvider_FWD_DEFINED__
typedef interface IDataProvider IDataProvider;

#endif 	/* __IDataProvider_FWD_DEFINED__ */


#ifndef __ICPUTempData_FWD_DEFINED__
#define __ICPUTempData_FWD_DEFINED__
typedef interface ICPUTempData ICPUTempData;

#endif 	/* __ICPUTempData_FWD_DEFINED__ */


#ifndef __IGPUTempData_FWD_DEFINED__
#define __IGPUTempData_FWD_DEFINED__
typedef interface IGPUTempData IGPUTempData;

#endif 	/* __IGPUTempData_FWD_DEFINED__ */


#ifndef __IGPUTempDataCollection_FWD_DEFINED__
#define __IGPUTempDataCollection_FWD_DEFINED__
typedef interface IGPUTempDataCollection IGPUTempDataCollection;

#endif 	/* __IGPUTempDataCollection_FWD_DEFINED__ */


#ifndef ___IDataProviderEvents_FWD_DEFINED__
#define ___IDataProviderEvents_FWD_DEFINED__
typedef interface _IDataProviderEvents _IDataProviderEvents;

#endif 	/* ___IDataProviderEvents_FWD_DEFINED__ */


#ifndef __DataProvider_FWD_DEFINED__
#define __DataProvider_FWD_DEFINED__

#ifdef __cplusplus
typedef class DataProvider DataProvider;
#else
typedef struct DataProvider DataProvider;
#endif /* __cplusplus */

#endif 	/* __DataProvider_FWD_DEFINED__ */


#ifndef ___ICPUTempDataEvents_FWD_DEFINED__
#define ___ICPUTempDataEvents_FWD_DEFINED__
typedef interface _ICPUTempDataEvents _ICPUTempDataEvents;

#endif 	/* ___ICPUTempDataEvents_FWD_DEFINED__ */


#ifndef __CPUTempData_FWD_DEFINED__
#define __CPUTempData_FWD_DEFINED__

#ifdef __cplusplus
typedef class CPUTempData CPUTempData;
#else
typedef struct CPUTempData CPUTempData;
#endif /* __cplusplus */

#endif 	/* __CPUTempData_FWD_DEFINED__ */


#ifndef ___IGPUTempDataEvents_FWD_DEFINED__
#define ___IGPUTempDataEvents_FWD_DEFINED__
typedef interface _IGPUTempDataEvents _IGPUTempDataEvents;

#endif 	/* ___IGPUTempDataEvents_FWD_DEFINED__ */


#ifndef __GPUTempData_FWD_DEFINED__
#define __GPUTempData_FWD_DEFINED__

#ifdef __cplusplus
typedef class GPUTempData GPUTempData;
#else
typedef struct GPUTempData GPUTempData;
#endif /* __cplusplus */

#endif 	/* __GPUTempData_FWD_DEFINED__ */


#ifndef __GPUTempDataCollection_FWD_DEFINED__
#define __GPUTempDataCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class GPUTempDataCollection GPUTempDataCollection;
#else
typedef struct GPUTempDataCollection GPUTempDataCollection;
#endif /* __cplusplus */

#endif 	/* __GPUTempDataCollection_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_DataSrv_0000_0000 */
/* [local] */ 





typedef /* [helpstring] */ 
enum SourceType
    {
        PDH	= 0,
        WMI	= 1,
        _Min	= PDH,
        _Max	= WMI
    } 	SourceType;



extern RPC_IF_HANDLE __MIDL_itf_DataSrv_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_DataSrv_0000_0000_v0_0_s_ifspec;

#ifndef __IDataProvider_INTERFACE_DEFINED__
#define __IDataProvider_INTERFACE_DEFINED__

/* interface IDataProvider */
/* [unique][oleautomation][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IDataProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1623b515-ff0c-4473-b388-3e96e6bfade0")
    IDataProvider : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CpuTemp( 
            /* [retval][out] */ ICPUTempData **ppProvider) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GpuTemp( 
            /* [retval][out] */ IGPUTempDataCollection **ppCollectionProvider) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDataProviderVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDataProvider * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDataProvider * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDataProvider * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDataProvider * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDataProvider * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDataProvider * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDataProvider * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IDataProvider, get_CpuTemp)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CpuTemp )( 
            IDataProvider * This,
            /* [retval][out] */ ICPUTempData **ppProvider);
        
        DECLSPEC_XFGVIRT(IDataProvider, get_GpuTemp)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GpuTemp )( 
            IDataProvider * This,
            /* [retval][out] */ IGPUTempDataCollection **ppCollectionProvider);
        
        END_INTERFACE
    } IDataProviderVtbl;

    interface IDataProvider
    {
        CONST_VTBL struct IDataProviderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDataProvider_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDataProvider_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDataProvider_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDataProvider_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDataProvider_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDataProvider_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDataProvider_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDataProvider_get_CpuTemp(This,ppProvider)	\
    ( (This)->lpVtbl -> get_CpuTemp(This,ppProvider) ) 

#define IDataProvider_get_GpuTemp(This,ppCollectionProvider)	\
    ( (This)->lpVtbl -> get_GpuTemp(This,ppCollectionProvider) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDataProvider_INTERFACE_DEFINED__ */


#ifndef __ICPUTempData_INTERFACE_DEFINED__
#define __ICPUTempData_INTERFACE_DEFINED__

/* interface ICPUTempData */
/* [unique][oleautomation][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICPUTempData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d341f25a-a80d-48d3-b07a-f1f9d5bca634")
    ICPUTempData : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Source( 
            /* [retval][out] */ SourceType *pSourceType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Source( 
            /* [in] */ SourceType sourceType) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICPUTempDataVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICPUTempData * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICPUTempData * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICPUTempData * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICPUTempData * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICPUTempData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICPUTempData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICPUTempData * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(ICPUTempData, get_Source)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Source )( 
            ICPUTempData * This,
            /* [retval][out] */ SourceType *pSourceType);
        
        DECLSPEC_XFGVIRT(ICPUTempData, put_Source)
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Source )( 
            ICPUTempData * This,
            /* [in] */ SourceType sourceType);
        
        END_INTERFACE
    } ICPUTempDataVtbl;

    interface ICPUTempData
    {
        CONST_VTBL struct ICPUTempDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICPUTempData_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICPUTempData_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICPUTempData_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICPUTempData_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICPUTempData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICPUTempData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICPUTempData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICPUTempData_get_Source(This,pSourceType)	\
    ( (This)->lpVtbl -> get_Source(This,pSourceType) ) 

#define ICPUTempData_put_Source(This,sourceType)	\
    ( (This)->lpVtbl -> put_Source(This,sourceType) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICPUTempData_INTERFACE_DEFINED__ */


#ifndef __IGPUTempData_INTERFACE_DEFINED__
#define __IGPUTempData_INTERFACE_DEFINED__

/* interface IGPUTempData */
/* [unique][oleautomation][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IGPUTempData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8d2a7171-ce2a-403c-9358-6bc065fb19be")
    IGPUTempData : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [retval][out] */ long *pIndex) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *ppName) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGPUTempDataVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGPUTempData * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGPUTempData * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGPUTempData * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGPUTempData * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGPUTempData * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGPUTempData * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGPUTempData * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IGPUTempData, get_Index)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Index )( 
            IGPUTempData * This,
            /* [retval][out] */ long *pIndex);
        
        DECLSPEC_XFGVIRT(IGPUTempData, get_Name)
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IGPUTempData * This,
            /* [retval][out] */ BSTR *ppName);
        
        END_INTERFACE
    } IGPUTempDataVtbl;

    interface IGPUTempData
    {
        CONST_VTBL struct IGPUTempDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGPUTempData_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGPUTempData_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGPUTempData_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGPUTempData_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGPUTempData_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGPUTempData_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGPUTempData_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGPUTempData_get_Index(This,pIndex)	\
    ( (This)->lpVtbl -> get_Index(This,pIndex) ) 

#define IGPUTempData_get_Name(This,ppName)	\
    ( (This)->lpVtbl -> get_Name(This,ppName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGPUTempData_INTERFACE_DEFINED__ */


#ifndef __IGPUTempDataCollection_INTERFACE_DEFINED__
#define __IGPUTempDataCollection_INTERFACE_DEFINED__

/* interface IGPUTempDataCollection */
/* [unique][oleautomation][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IGPUTempDataCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("706279aa-4dc8-4689-92fa-ec656b0c5f8f")
    IGPUTempDataCollection : public IDispatch
    {
    public:
        virtual /* [hidden][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppUnk) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ IGPUTempData **ppGPUTempData) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pCount) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGPUTempDataCollectionVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGPUTempDataCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGPUTempDataCollection * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGPUTempDataCollection * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IGPUTempDataCollection * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IGPUTempDataCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IGPUTempDataCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IGPUTempDataCollection * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IGPUTempDataCollection, get__NewEnum)
        /* [hidden][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IGPUTempDataCollection * This,
            /* [retval][out] */ IUnknown **ppUnk);
        
        DECLSPEC_XFGVIRT(IGPUTempDataCollection, get_Item)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IGPUTempDataCollection * This,
            /* [in] */ long index,
            /* [retval][out] */ IGPUTempData **ppGPUTempData);
        
        DECLSPEC_XFGVIRT(IGPUTempDataCollection, get_Count)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IGPUTempDataCollection * This,
            /* [retval][out] */ long *pCount);
        
        END_INTERFACE
    } IGPUTempDataCollectionVtbl;

    interface IGPUTempDataCollection
    {
        CONST_VTBL struct IGPUTempDataCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGPUTempDataCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGPUTempDataCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGPUTempDataCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGPUTempDataCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IGPUTempDataCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IGPUTempDataCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IGPUTempDataCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IGPUTempDataCollection_get__NewEnum(This,ppUnk)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppUnk) ) 

#define IGPUTempDataCollection_get_Item(This,index,ppGPUTempData)	\
    ( (This)->lpVtbl -> get_Item(This,index,ppGPUTempData) ) 

#define IGPUTempDataCollection_get_Count(This,pCount)	\
    ( (This)->lpVtbl -> get_Count(This,pCount) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGPUTempDataCollection_INTERFACE_DEFINED__ */



#ifndef __DataSrvLib_LIBRARY_DEFINED__
#define __DataSrvLib_LIBRARY_DEFINED__

/* library DataSrvLib */
/* [version][uuid] */ 



EXTERN_C const IID LIBID_DataSrvLib;

#ifndef ___IDataProviderEvents_DISPINTERFACE_DEFINED__
#define ___IDataProviderEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IDataProviderEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IDataProviderEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("16cc38a3-da74-4c92-a05a-fb483f03a8d9")
    _IDataProviderEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IDataProviderEventsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IDataProviderEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IDataProviderEvents * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IDataProviderEvents * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IDataProviderEvents * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IDataProviderEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IDataProviderEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IDataProviderEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IDataProviderEventsVtbl;

    interface _IDataProviderEvents
    {
        CONST_VTBL struct _IDataProviderEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IDataProviderEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IDataProviderEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IDataProviderEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IDataProviderEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IDataProviderEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IDataProviderEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IDataProviderEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IDataProviderEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DataProvider;

#ifdef __cplusplus

class DECLSPEC_UUID("50539d6d-636e-4f22-b1de-c01dadcaa86f")
DataProvider;
#endif

#ifndef ___ICPUTempDataEvents_DISPINTERFACE_DEFINED__
#define ___ICPUTempDataEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ICPUTempDataEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__ICPUTempDataEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("35ef5d4d-2bc2-40a6-9ba6-34d0fc521bb8")
    _ICPUTempDataEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ICPUTempDataEventsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ICPUTempDataEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ICPUTempDataEvents * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ICPUTempDataEvents * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ICPUTempDataEvents * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ICPUTempDataEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ICPUTempDataEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ICPUTempDataEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _ICPUTempDataEventsVtbl;

    interface _ICPUTempDataEvents
    {
        CONST_VTBL struct _ICPUTempDataEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ICPUTempDataEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ICPUTempDataEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ICPUTempDataEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ICPUTempDataEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ICPUTempDataEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ICPUTempDataEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ICPUTempDataEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ICPUTempDataEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CPUTempData;

#ifdef __cplusplus

class DECLSPEC_UUID("f44a631e-725d-4d6d-8e87-c181be87b694")
CPUTempData;
#endif

#ifndef ___IGPUTempDataEvents_DISPINTERFACE_DEFINED__
#define ___IGPUTempDataEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IGPUTempDataEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IGPUTempDataEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("3460de00-e39a-4f5b-9860-2cc52438b67b")
    _IGPUTempDataEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IGPUTempDataEventsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IGPUTempDataEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IGPUTempDataEvents * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IGPUTempDataEvents * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IGPUTempDataEvents * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IGPUTempDataEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IGPUTempDataEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IGPUTempDataEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IGPUTempDataEventsVtbl;

    interface _IGPUTempDataEvents
    {
        CONST_VTBL struct _IGPUTempDataEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IGPUTempDataEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IGPUTempDataEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IGPUTempDataEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IGPUTempDataEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IGPUTempDataEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IGPUTempDataEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IGPUTempDataEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IGPUTempDataEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GPUTempData;

#ifdef __cplusplus

class DECLSPEC_UUID("a5135fac-5594-465b-a6c2-48c5b8d34f21")
GPUTempData;
#endif

EXTERN_C const CLSID CLSID_GPUTempDataCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("9a29e514-0cc0-4872-a5d7-cce21b0fe153")
GPUTempDataCollection;
#endif
#endif /* __DataSrvLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


