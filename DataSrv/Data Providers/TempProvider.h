#pragma once

#include "../Utilities/EventWorkerThread.h"

class CTempProvider : public EventWorkerThread<float>
{
public:
    using TBase = EventWorkerThread<float>;

    // Construction

    CTempProvider();
    ~CTempProvider() override;
};
