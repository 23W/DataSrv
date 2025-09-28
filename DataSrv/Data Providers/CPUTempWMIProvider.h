#pragma once

#include "CPUTempProvider.h"

class CCPUTempWMIProvider : public CCPUTempProvider
{
public:
    using TBase = CCPUTempProvider;

    // Construction

    CCPUTempWMIProvider();
    ~CCPUTempWMIProvider() override;

protected:

    // Overrides

    void RunThread() override;
};