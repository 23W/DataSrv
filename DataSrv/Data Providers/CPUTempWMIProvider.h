#pragma once

#include "CPUTempProvider.h"

class CCPUTempWMIProvider : public CCPUTempProvider
{
public:
    using TBase = CCPUTempProvider;

    // Construction

    CCPUTempWMIProvider();
    ~CCPUTempWMIProvider();

protected:

    // Overrides

    void RunThread() override;
};