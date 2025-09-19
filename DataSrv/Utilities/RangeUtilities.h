#pragma once


class CRangeUtilities
{
public:
    template<typename T>
    static constexpr bool IsBetween(const T& val, const T& min, const T& max)
    {
        return val >= min && val <= max;
    }
};