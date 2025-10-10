#pragma once

#include <stdexcept>
#include <string>
#include <type_traits>

template<typename TException>
class status_error : public TException
{
public:
    using TBase = TException;
    using TStatusCode = unsigned int;

    status_error(TStatusCode code, const std::string& message) : TBase(message), m_code(code) {}
    status_error(TStatusCode code, const char* message) : TBase(message), m_code(code) {}

    status_error(status_error&& other) = default;
    status_error(const status_error& other) = default;

    status_error& operator = (status_error&& other) = default;
    status_error& operator = (const status_error& other) = default;

    TStatusCode status_code() const noexcept { return m_code; }

protected:

    static_assert(std::is_base_of_v<std::exception, TException>, "Invalid base exception");

private:

    TStatusCode m_code = 0;
};

using status_logic_error = status_error<std::logic_error>;
using status_runtime_error = status_error<std::runtime_error>;
