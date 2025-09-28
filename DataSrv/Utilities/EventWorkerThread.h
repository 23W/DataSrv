#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "Event.h"

template<typename...TArgs>
class EventWorkerThread
{
public:
    using TEvent = Event<TArgs...>;
    using TId = TEvent::TId;
    using THandler = TEvent::THandler;
    using TLock = std::mutex;

    // Construction

    EventWorkerThread()
    {
    }

    virtual ~EventWorkerThread()
    {
        StopThread();
    }

    // Methods

    TId Subscrive(THandler&& handler)
    {
        auto runThread = false;
        auto id = TId{};

        {
            std::lock_guard<TLock> lock(m_lock);

            const auto wasEmpty = m_event.IsEmpty();
            id = m_event.Subscribe(std::move(handler));
            const auto isEmpty = m_event.IsEmpty();

            runThread = wasEmpty && !isEmpty;
        }

        if (runThread)
        {
            RunThread();
        }

        return id;
    }

    void Unsubscrive(const TId& id)
    {
        auto stopThread = false;

        {
            std::lock_guard<TLock> lock(m_lock);

            m_event.Unsubscribe(id);
            stopThread = m_event.IsEmpty();
        }

        if (stopThread)
        {
            StopThread();
        }
    }

protected:

    // Helper Methods

    virtual void RunThread() = 0;
    //  Example of implementation
    //{
    //    if (m_threadRunning)
    //    {
    //        return;
    //    }
    //
    //    m_thread = std::thread([this]()
    //    {
    //        std::unique_lock<TLock> lock(m_lock);
    //        m_threadRunning = true;
    //
    //        while (m_threadRunning)
    //        {
    //            CoInitializeEx(NULL, COINIT_MULTITHREADED); // if you need COM
    // 
    //            // collect data
    //
    //            lock.unlock();
    //            m_event.Notify(/* data */);
    //            lock.lock();
    //
    //            m_threadWakeup.wait_for(lock, std::chrono::milliseconds(/*collecting timeout*/), [this]() { return !m_threadRunning; });
    //        }
    //    });
    //}

    virtual void StopThread()
    {
        m_threadRunning = false;
        m_threadWakeup.notify_one();

        if (m_thread.joinable())
        {
            m_thread.join();
        }
    }


    // Members

    TEvent m_event;

    TLock m_lock;
    std::condition_variable m_threadWakeup;
    std::atomic_bool m_threadRunning;
    std::thread m_thread;

    // Deleted methods

    EventWorkerThread(const EventWorkerThread&) = delete;
    EventWorkerThread(EventWorkerThread&&) = delete;
    EventWorkerThread& operator = (const EventWorkerThread&) = delete;
    EventWorkerThread& operator = (EventWorkerThread&&) = delete;
};
