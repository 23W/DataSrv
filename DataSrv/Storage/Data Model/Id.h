#pragma once

#include <array>
#include <cstdint>
#include <guiddef.h>
#include "../../Utilities/HashUtilities.h"

struct Id
{
    std::array<uint8_t, 16> Data = { 0 };

    Id() = default;
    Id(const Id&) = default;
    Id(Id&&) = default;
    explicit Id(const GUID& guid)
    {
        operator = (guid);
    }

    Id& operator = (const Id&) = default;
    Id& operator = (Id&&) = default;

    Id& operator = (const GUID& guid) noexcept
    {
        static_assert(sizeof(Id) == sizeof(GUID), "Id and GUID must have same size");
        std::memcpy(Data.data(), &guid, sizeof(GUID));

        return *this;
    }

    explicit operator GUID() const noexcept
    {
        auto guid = GUID{};
        std::memcpy(&guid, Data.data(), sizeof(GUID));

        return guid;
    }

    auto operator<=>(const Id&) const = default;

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
