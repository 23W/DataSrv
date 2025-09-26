#pragma once

#include "ComUtilities.h"
#include "TypeUtilities.h"


template<typename T, typename ThreadModel>
class CComValueCollectionImpl
{
public:
    using TValue = T;
    using TVariantEnum = ATL::CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, ATL::_Copy<VARIANT>, ThreadModel>;
    using TComVariantEnum = ATL::CComObject<TVariantEnum>;

    CComValueCollectionImpl() {}
    virtual ~CComValueCollectionImpl() {}

    STDMETHOD(get__NewEnum)(IUnknown** ppUnk, IUnknown* pThis = nullptr)
    {
        auto count = 0L;
        auto hr = get_Count(&count);
        if (SUCCEEDED(hr))
        {
            auto pElements = new ATL::CComVariant[count];

            for (auto index = CTypeUtilities::type_of(count, 0); index < count; index++)
            {
                auto value = TValue{};
                hr = get_Item(index + 1, &value);
                if (SUCCEEDED(hr))
                {
                    pElements[index] = ATL::CComVariant(value);
                }
                else
                {
                    delete[] pElements;
                    break;
                }
            }

            if (SUCCEEDED(hr))
            {
                hr = CComUtilities::CreateCOM<TVariantEnum>(ppUnk, [&](TVariantEnum* pEnumObject)
                                                            {
                                                                auto hr = pEnumObject->Init(pElements,
                                                                                            std::next(pElements, count),
                                                                                            pThis, ATL::AtlFlagTakeOwnership);
                                                                if (FAILED(hr))
                                                                {
                                                                    delete[] pElements;
                                                                }

                                                                return hr;
                                                            });
            }
        }

        return hr;
    }

    STDMETHOD(get_Item)(long index, TValue* pValue) = 0;
    STDMETHOD(get_Count)(long* pVal) = 0;
};


template<typename T, typename ThreadModel>
class CComUnkCollectionImpl
{
public:
    using TInterface = T;
    using TVariantEnum = ATL::CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, ATL::_Copy<VARIANT>, ThreadModel>;
    using TComVariantEnum = ATL::CComObject<TVariantEnum>;

    CComUnkCollectionImpl()
    {
        static_assert(std::is_base_of<IUnknown, TInterface>::value, "TInterface must inherit IUnknown");
    }

    virtual ~CComUnkCollectionImpl() {}

    STDMETHOD(get__NewEnum)(IUnknown** ppUnk, IUnknown* pThis = nullptr)
    {
        auto count = 0L;
        auto hr = get_Count(&count);
        if (SUCCEEDED(hr))
        {
            auto pElements = new ATL::CComVariant[count];

            for (auto index = CTypeUtilities::type_of(count, 0); index < count; index++)
            {
                ATL::CComPtr<TInterface> spItemInterface;
                hr = get_Item(index + 1, &spItemInterface);
                if (SUCCEEDED(hr))
                {
                    pElements[index] = ATL::CComVariant(spItemInterface);
                }
                else
                {
                    delete[] pElements;
                    break;
                }
            }

            if (SUCCEEDED(hr))
            {
                hr = CComUtilities::CreateCOM<TVariantEnum>(ppUnk, [&](TVariantEnum* pEnumObject)
                                                           {
                                                               auto hr = pEnumObject->Init(pElements,
                                                                                           std::next(pElements, count),
                                                                                           pThis, ATL::AtlFlagTakeOwnership);
                                                               if (FAILED(hr))
                                                               {
                                                                   delete[] pElements;
                                                               }
                                                               return hr;
                                                           });
            }
        }

        return hr;
    }

    STDMETHOD(get_Item)(long index, TInterface** ppValue) = 0;
    STDMETHOD(get_Count)(long* pVal) = 0;
};

template<typename T, typename ThreadModel>
class CComDispCollectionImpl : public CComUnkCollectionImpl<T, ThreadModel>
{
public:
    using TBase = CComUnkCollectionImpl<T, ThreadModel>;
    using TInterface = TBase::TInterface;

    CComDispCollectionImpl()
    {
        static_assert(std::is_base_of<IDispatch, TInterface>::value, "TInterface must inherit IUnknown");
    }

    virtual ~CComDispCollectionImpl() {}
};
