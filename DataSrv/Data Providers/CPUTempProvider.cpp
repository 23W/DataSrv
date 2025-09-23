#include "pch.h"

#include "CPUTempProvider.h"

// Construction

CCPUTempProvider::CCPUTempProvider()
{
}

CCPUTempProvider::~CCPUTempProvider()
{
    StopThread();
}

// Methods

CCPUTempProvider::TSampleEvent::TId CCPUTempProvider::Subscrive(TSampleEvent::THandler&& handler)
{
    auto runThread = false;
    auto id = TSampleEvent::TId{};

    {
        std::lock_guard<TLock> lock(m_lock);

        const auto wasEmpty = m_sampleEvent.IsEmpty();
        id = m_sampleEvent.Subscribe(std::move(handler));
        const auto isEmpty = m_sampleEvent.IsEmpty();

        runThread = wasEmpty && !isEmpty;
    }

    if (runThread)
    {
        RunThread();
    }

    return id;
}

void CCPUTempProvider::Unsubscrive(const TSampleEvent::TId& id)
{
    auto stopThread = false;

    {
        std::lock_guard<TLock> lock(m_lock);

        m_sampleEvent.Unsubscribe(id);
        stopThread = m_sampleEvent.IsEmpty();
    }

    if (stopThread)
    {
        StopThread();
    }
}

// Helper Methods

void CCPUTempProvider::StopThread()
{
    {
        std::lock_guard<TLock> lock(m_lock);
        m_threadRunning = false;
    }

    m_threadWakeup.notify_one();

    if (m_thread.joinable())
    {
        m_thread.join();
    }
}
