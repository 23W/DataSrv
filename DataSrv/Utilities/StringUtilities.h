#pragma once

#include <atlstr.h>
#include <utility>

class CStringUtilities
{
public:

    template<typename ...TArgs>
    static CString Format(LPCTSTR formatStr, TArgs&&... args)
    {
        CString res;
        res.Format(formatStr, std::forward<TArgs>(args)...);

        return res;
    }
};