#pragma once

#include "ComUtilities.h"
#include "TypeUtilities.h"


template<typename T, typename ThreadModel>
class CComValueCollectionImpl
{
public:
    using TValue = T;
    using TVariantCopy = ATL::_Copy<VARIANT>;
    using TVariantEnum = ATL::CComEnum<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, TVariantCopy, ThreadModel>;

    CComValueCollectionImpl() {}
    virtual ~CComValueCollectionImpl() {}

    STDMETHOD(get__NewEnum)(IUnknown** ppUnk, IUnknown* pThis = nullptr)
    {
        auto count = 0L;
        auto hr = get_Count(&count);
        if (SUCCEEDED(hr))
        {
            auto pElements = CreateElementsArray(count);

            for (auto index = CTypeUtilities::type_of(count, 0); index < count; index++)
            {
                auto value = TValue{};
                hr = get_Item(index + 1, &value);
                if (SUCCEEDED(hr))
                {
                    ATL::CComVariant(value).Detach(&pElements[index]);
                }
                else
                {
                    DeleteElementsArray(pElements, count);
                    break;
                }
            }

            if (SUCCEEDED(hr))
            {
                hr = CComUtilities::CreateCom<TVariantEnum>(ppUnk, [&](TVariantEnum* pEnumObject)
                                                            {
                                                                auto hr = pEnumObject->Init(pElements,
                                                                                            std::next(pElements, count),
                                                                                            pThis, ATL::AtlFlagTakeOwnership);
                                                                if (FAILED(hr))
                                                                {
                                                                    DeleteElementsArray(pElements, count);
                                                                }

                                                                return hr;
                                                            });
            }
        }

        return hr;
    }

    STDMETHOD(get_Item)(long index, TValue* pValue) = 0;
    STDMETHOD(get_Count)(long* pVal) = 0;

protected:

    VARIANT* CreateElementsArray(size_t count)
    {
        auto pElements = new VARIANT[count];
        for (auto index = CTypeUtilities::type_of(count, 0); index < count; index++)
        {
            TVariantCopy::init(&pElements[index]);
        }

        return pElements;
    }

    void DeleteElementsArray(VARIANT* pElements, size_t count)
    {
        for (auto index = CTypeUtilities::type_of(count, 0); index < count; index++)
        {
            TVariantCopy::destroy(&pElements[index]);
        }

        delete[] pElements;
    }
};


template<typename T, typename ThreadModel>
class CComUnkCollectionImpl : public CComValueCollectionImpl<T*, ThreadModel>
{
public:
    using TBase = CComValueCollectionImpl<T*, ThreadModel>;
    using TInterface = T;
    using TVariantEnum = TBase::TVariantEnum;

    CComUnkCollectionImpl()
    {
        static_assert(std::is_base_of<IUnknown, TInterface>::value, "TInterface must inherit IUnknown");
    }

    STDMETHOD(get__NewEnum)(IUnknown** ppUnk, IUnknown* pThis = nullptr) override
    {
        auto count = 0L;
        auto hr = get_Count(&count);
        if (SUCCEEDED(hr))
        {
            auto pElements = TBase::CreateElementsArray(count);

            for (auto index = CTypeUtilities::type_of(count, 0); index < count; index++)
            {
                ATL::CComPtr<TInterface> spItemInterface;
                hr = get_Item(index + 1, &spItemInterface);
                if (SUCCEEDED(hr))
                {
                    ATL::CComVariant(spItemInterface).Detach(&pElements[index]);
                }
                else
                {
                    TBase::DeleteElementsArray(pElements, count);
                    break;
                }
            }

            if (SUCCEEDED(hr))
            {
                hr = CComUtilities::CreateCom<TVariantEnum>(ppUnk, [&](TVariantEnum* pEnumObject)
                                                           {
                                                               auto hr = pEnumObject->Init(pElements,
                                                                                           std::next(pElements, count),
                                                                                           pThis, ATL::AtlFlagTakeOwnership);
                                                               if (FAILED(hr))
                                                               {
                                                                   TBase::DeleteElementsArray(pElements, count);
                                                               }
                                                               return hr;
                                                           });
            }
        }

        return hr;
    }

    STDMETHOD(get_Item)(long index, TInterface** ppItemInterface) override = 0;
    STDMETHOD(get_Count)(long* pVal) override = 0;
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
