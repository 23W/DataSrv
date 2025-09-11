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
    ~CCPUTempProvider();

    // Methods

    TSampleEvent::TId Subscrive(TSampleEvent::THandler&& handler);
    void Unsubscrive(const TSampleEvent::TId& id);

private:

    // Helper Methods

    void RunThread();
    void StopThread();

    // Members

    mutable TLock m_lock;

    TSampleEvent m_sampleEvent;
    std::atomic_bool m_running;
    std::thread m_thread;
};