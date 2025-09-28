#pragma once

#include <atlbase.h>
#include <atlcom.h>
#include <array>
#include <functional>
#include <utility>

class CComUtilities
{
public:

    template<typename TComClass, typename TInterface>
    static HRESULT CreateCom(TInterface** ppInterface, std::function<HRESULT(TComClass*)> initializer = nullptr)
    {
        ATL::CComPtr<ATL::CComObject<TComClass>> spObject;
        auto hr = ATL::CComObject<TComClass>::CreateInstance(&spObject);
        if (FAILED(hr))
        {
            return hr;
        }

        if (!!initializer)
        {
            hr = initializer(spObject);
            if (FAILED(hr))
            {
                return hr;
            }
        }

        hr = spObject.QueryInterface(ppInterface);
        if (SUCCEEDED(hr))
        {
            spObject.Detach();
        }

        return hr;
    }

    template<typename TComClass, typename TComUnkVector, typename... TValues>
    static void FireEvent(TComClass* pObject, TComUnkVector& subscribers, DISPID eventId, TValues&&... args)
    {
        if (subscribers.GetSize() == 0)
        {
            return;
        }

        std::array<ATL::CComVariant, sizeof...(TValues)> params = {std::forward<TValues>(args)...};
        // Parameters are passed in reverse order for COM events!
        std::reverse(std::begin(params), std::end(params));

        CComVariant varResult;
        for (auto index = 0, count = subscribers.GetSize(); index < count; index++)
        {
            pObject->Lock();
            ATL::CComPtr<IDispatch> spSubscriberDispatch(reinterpret_cast<IDispatch*>(subscribers.GetAt(index)));
            pObject->Unlock();

            if (spSubscriberDispatch != nullptr)
            {
                VariantClear(&varResult);

                DISPPARAMS disp = { params.data(), nullptr, static_cast<UINT>(params.size()), 0U };
                spSubscriberDispatch->Invoke(eventId, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, nullptr, nullptr);
            }
        }
    }

    template<std::size_t size>
    static bool HasInterface(const std::array<IID, size>& data, REFIID iid)
    {
        return HasInterface(data.data(), data.size(), iid);
    }

    static bool HasInterface(const IID* pData, size_t count, REFIID iid)
    {
        auto res = false;
        for (auto it = pData, last = std::next(pData, count); it < last && !res; ++it)
        {
            res = InlineIsEqualGUID(*it, iid);
        }

        return res;
    }

    template<typename TComClass>
    static HRESULT ErrorInvalidPointer(TComClass* pObject, IID iid)
    {
        return pObject->Error(_T("Invalid pointer"), iid, E_POINTER);
    }

    template<typename TComClass>
    static HRESULT ErrorInvalidIndex(TComClass* pObject, IID iid)
    {
        return pObject->Error(_T("Invalid collection index"), iid, E_INVALIDARG);
    }
};
