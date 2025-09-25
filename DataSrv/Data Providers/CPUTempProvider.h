#pragma once

#include "TempProvider.h"

class CCPUTempProvider : public CTempProvider
{
public:
    using TBase = CTempProvider;

    // Construction

    CCPUTempProvider();
    ~CCPUTempProvider() override;
};