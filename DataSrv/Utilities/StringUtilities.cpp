#include "pch.h"

#include "StringUtilities.h"

ATL::CStringW CStringUtilities::Utf8ToCString(const std::string& utf8Stream)
{
    return Utf8ToCString(utf8Stream.c_str(), utf8Stream.length());
}

ATL::CStringW CStringUtilities::Utf8ToCString(const char* pUtf8Stream, size_t streamLength)
{
    ATL::CStringW res;

    if (pUtf8Stream == nullptr ||
        streamLength == 0)
    {
        return res;
    }

    const auto requiredLength = MultiByteToWideChar(CP_UTF8, 0, pUtf8Stream, static_cast<int>(streamLength), nullptr, 0);
    if (requiredLength > 0)
    {
        const auto pBuffer = res.GetBufferSetLength(requiredLength + 1);
        MultiByteToWideChar(CP_UTF8, 0, pUtf8Stream, static_cast<int>(streamLength), pBuffer, requiredLength);
        res.ReleaseBuffer(requiredLength);
    }

    return res;
}
