#pragma once

#include <atomic>
#include <thread>
#include <mutex>
#include "..\Utilities\Event.h"

class CCPUTempProvider
{
public:
    using TSampleEvent = Event<float>;
    using TLock = std::mutex;

    // Construction

    CCPUTempProvider();
    virtual ~CCPUTempProvider();

    // Methods

    TSampleEvent::TId Subscrive(TSampleEvent::THandler&& handler);
    void Unsubscrive(const TSampleEvent::TId& id);

protected:

    // Helper Methods

    virtual void RunThread() = 0;
    virtual void StopThread();

    // Members

    mutable TLock m_lock;

    TSampleEvent m_sampleEvent;
    std::atomic_bool m_running;
    std::thread m_thread;
};