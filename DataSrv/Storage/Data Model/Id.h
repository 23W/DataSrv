#pragma once

#include <array>
#include <bit>
#include <cstdint>
#include <guiddef.h>
#include "../../Utilities/HashUtilities.h"

struct Id
{
    using DataType = std::array<uint8_t, 16>;

    // Properties

    DataType Data = { 0 };

    // Construction

    constexpr Id() = default;
    constexpr Id(const Id&) = default;
    constexpr Id(Id&&) = default;
    constexpr explicit Id(const GUID& guid)
    {
        operator = (guid);
    }

    // Operators

    constexpr Id& operator = (const Id&) = default;
    constexpr Id& operator = (Id&&) = default;

    constexpr Id& operator = (const GUID& guid) noexcept
    {
        static_assert(std::is_trivially_copyable_v<Id> &&
                      std::is_trivially_copyable_v<GUID> &&
                      sizeof(Id) == sizeof(GUID), "Id and GUID must have same size");
        Data = std::bit_cast<DataType>(guid);

        return *this;
    }

    constexpr explicit operator GUID() const noexcept
    {
        return std::bit_cast<GUID>(Data);
    }

    constexpr auto operator<=>(const Id&) const = default;

    static Id MakeNew() noexcept
    {
        auto guid = GUID_NULL;
        CoCreateGuid(&guid);
        return Id(guid);
    }
};


namespace std
{
    template <size_t size>
    struct hash<array<uint8_t, size>>
    {
        size_t operator()(const array<uint8_t, size>& data) const noexcept
        {
            const auto hash = CHashUtilities<sizeof(size_t)>::Hash(data.data(), data.size());
            return static_cast<size_t>(hash);
        }
    };

    template <>
    struct hash<Id>
    {
        size_t operator()(const Id& id) const noexcept
        {
            return hash<decltype(id.Data)>()(id.Data);
        }
    };
}
