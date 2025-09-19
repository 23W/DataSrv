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
    std::lock_guard<TLock> lock(m_lock);

    const auto wasEmpty = m_sampleEvent.IsEmpty();
    const auto id = m_sampleEvent.Subscribe(std::move(handler));
    const auto isEmpty = m_sampleEvent.IsEmpty();

    if (wasEmpty && !isEmpty)
    {
        RunThread();
    }

    return id;
}

void CCPUTempProvider::Unsubscrive(const TSampleEvent::TId& id)
{
    std::lock_guard<TLock> lock(m_lock);

    m_sampleEvent.Unsubscribe(id);

    if (m_sampleEvent.IsEmpty())
    {
        StopThread();
    }
}

// Helper Methods

void CCPUTempProvider::StopThread()
{
    m_running = false;

    if (m_thread.joinable())
    {
        m_thread.join();
    }
}
