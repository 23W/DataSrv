#pragma once

#include <atlbase.h>
#include <atlcom.h>
#include <array>
#include <utility>

class CComUtilities
{
    template<typename TComClass, typename TComUnkVector, typename... TValues>
    static void FireEvent(TComClass* pObject, const TComUnkVector& subscribers, DISPID eventId, TValues&&... args)
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
            ATL::CComPtr<IDispatch> spUnknown(reinterpret_cast<IDispatch*>(subscribers.GetAt(index)));
            pObject->Unlock();

            if (spUnknown != nullptr)
            {
                VariantClear(&varResult);

                DISPPARAMS disp = { params.data(), nullptr, static_cast<UINT>(params.size()), 0U };
                spDispatch->Invoke(eventId, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, nullptr, nullptr);
            }
        }
    }
};