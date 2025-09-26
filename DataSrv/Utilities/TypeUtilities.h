#pragma once
#include <type_traits>

class CTypeUtilities
{
public:

    // returns value of type T2 casted to non const\volatile version of T1
    template<typename T1, typename T2>
    static constexpr auto type_of_cv(T2 val) { return static_cast<std::remove_cv<T1>::type>(val); }

    // returns value of type T2 casted to non const\volatile version of T1.
    // T1 is deduced from the first argument
    template<typename T1, typename T2>
    static constexpr auto type_of_cv(T1&&, T2 val) { return type_of_cv<T1, T2>(val); }

    // returns value of type T2 casted to T1
    template<typename T1, typename T2>
    static constexpr auto type_of(T2 val) { return static_cast<T1>(val); }

    // returns value of type T2 casted to T1.
    // T1 is deduced from the first argument
    template<typename T1, typename T2>
    static constexpr auto type_of(T1&&, T2 val) { return type_of<typename std::remove_reference<T1>::type, T2>(val); }
};
