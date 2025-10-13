#include "pch.h"
#include <vector>
#include <base64.hpp>

#include "Id.h"

Id& Id::operator = (const std::string& str)
{
    auto value = base64::decode_into<std::vector<DataType::value_type>>(str);
    if (value.size() == Data.size())
    {
        std::memcpy(Data.data(), value.data(), value.size());
    }
    else
    {
        throw std::runtime_error("Invalid text length");
    }

    return *this;
}

Id::operator std::string() const
{
    auto res = base64::encode_into<std::string>(std::begin(Data), std::end(Data));
    return res;
}

Id Id::MakeNew() noexcept
{
    auto guid = GUID_NULL;
    CoCreateGuid(&guid);
    return Id(guid);
}
