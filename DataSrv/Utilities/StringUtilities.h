#pragma once

#include <atlstr.h>
#include <string>
#include <format>
#include <utility>

class CStringUtilities
{
public:

    template<typename ...TArgs>
    static ATL::CString Format(LPCTSTR formatStr, TArgs&&... args)
    {
        ATL::CString res;
        res.Format(formatStr, std::forward<TArgs>(args)...);

        return res;
    }

    static ATL::CStringW Utf8ToCString(const std::string& utf8Stream);
    static ATL::CStringW Utf8ToCString(const char* pUtf8Stream, size_t streamLength);
};
