#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
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

    TSampleEvent m_sampleEvent;

    TLock m_lock;
    std::condition_variable m_threadWakeup;
    std::thread m_thread;
    bool m_threadRunning;
};