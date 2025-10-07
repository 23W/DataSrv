#pragma once

#include <array>
#include <bit>
#include <cstdint>
#include <type_traits>
#include <xxHash/xxhash.h>

template<size_t hashSize>
struct SHashType
{
    using value_type =
        std::conditional_t<hashSize == 1, uint8_t,
        std::conditional_t<hashSize == 2, uint16_t,
        std::conditional_t<hashSize == 4, uint32_t,
        std::conditional_t<hashSize == 8, uint64_t, std::array<std::uint8_t, hashSize>>>>>;

    // Properties

    value_type Value{};
    
    // Construction

    constexpr SHashType() = default;
    constexpr SHashType(const SHashType& src) = default;
    constexpr SHashType(SHashType&& src) = default;
    constexpr SHashType(const value_type& src) : Value(src) {}
    constexpr SHashType(value_type&& src) : Value(std::move(src)) {}

    // Operators

    constexpr operator value_type() const noexcept { return Value; }

    constexpr SHashType& operator = (const SHashType& src) noexcept = default;
    constexpr SHashType& operator = (SHashType&& src) noexcept = default;
    constexpr SHashType& operator = (const value_type& src) noexcept { Value = src; return *this; }
    constexpr SHashType& operator = (value_type&& src) noexcept { Value = std::move(src); return *this; }

    constexpr bool operator==(const SHashType&) const = default;
    constexpr bool operator!=(const SHashType&) const = default;

    // Conversion from\to compatible trivial types

    template<typename T>
    constexpr explicit SHashType(const T& src)
    {
        *this = src;
    }

    template<typename T>
    constexpr SHashType& operator = (const T& src) noexcept
    {
        static_assert(std::is_trivially_copyable_v<T> &&
                      std::is_standard_layout_v<T> &&
                      sizeof(T) == sizeof(value_type), "Types must have equal size and be trivially copyable");

        Value = std::bit_cast<value_type>(src);
        return *this;
    }

    template<typename T>
    constexpr T As() const noexcept
    {
        static_assert(std::is_trivially_copyable_v<T> &&
                      std::is_standard_layout_v<T> &&
                      sizeof(T) == sizeof(value_type), "Types must have equal size and be trivially copyable");

        return std::bit_cast<T>(Value);
    }
};

template<size_t hashSize>
class CHashUtilities
{
public:
    using HashType = SHashType<hashSize>;

    static HashType Hash(const void* pData, size_t count, HashType seed = HashType{})
    {
        static_assert(hashSize == 4 ||
                      hashSize == 8 ||
                      hashSize == 16, "unsupported hash size");
    }
};

template<>
CHashUtilities<4>::HashType CHashUtilities<4>::Hash(const void* pData, size_t count, HashType seed)
{
    const auto hash = XXH32(pData, count, static_cast<XXH32_hash_t>(seed));
    return hash;
}

template<>
CHashUtilities<8>::HashType CHashUtilities<8>::Hash(const void* pData, size_t count, HashType seed)
{
    const auto hash = XXH3_64bits_withSeed(pData, count, static_cast<XXH64_hash_t>(seed));
    return hash;
}

template<>
CHashUtilities<16>::HashType CHashUtilities<16>::Hash(const void* pData, size_t count, HashType seed)
{
    auto xxSeed = XXH64_hash_t{};
    if (seed != HashType{})
    {
        xxSeed = XXH3_64bits(seed.Value.data(), sizeof(seed.Value));
    }

    const auto hash = XXH3_128bits_withSeed(pData, count, xxSeed);
    return SHashType<16>(hash);
}
