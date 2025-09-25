#pragma once

#include "CPUTempProvider.h"

class CCPUTempPDHProvider : public CCPUTempProvider
{
public:
    using TBase = CCPUTempProvider;

    // Construction

    CCPUTempPDHProvider();
    ~CCPUTempPDHProvider() override;

protected:

    // Overrides

    void RunThread() override;
};