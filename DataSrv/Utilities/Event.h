#pragma once

#include <mutex>
#include <shared_mutex>
#include <functional>
#include <unordered_map>


template<typename...TArgs>
class Event
{
public:
    using THandler = std::function<void(TArgs...)>;
    using TId = size_t;
    using TMap = std::unordered_map<TId, THandler>;

    bool IsEmpty() const
    {
        return m_handlers.empty();
    }

    TId Subscribe(THandler&& handler)
    {
        if (m_nextId == 0)
        {
            ++m_nextId;
        }

        const auto nextId = m_nextId++;
        m_handlers.emplace(nextId, std::move(handler));

        return nextId;
    }

    void Unsubscribe(const TId& id)
    {
        m_handlers.erase(id);
    }

    void Notify(const TArgs&... args) const
    {
        for (const auto& kvp : m_handlers)
        {
            const auto& handler = std::get<1>(kvp);
            handler(args...);
        }
    }

protected:

    TMap m_handlers;
    TId m_nextId = 0;
};


template<typename...TArgs>
class EventShared : public Event<TArgs...>
{
public:
    using TBase = Event<TArgs...>;
    using THandler = std::function<void(TArgs...)>;
    using TLock = std::shared_mutex;
    using TId = size_t;
    using TMap = std::unordered_map<TId, THandler>;

    bool IsEmpty() const
    {
        std::shared_lock<TLock> guard(m_lock);
        return TBase::IsEmpty();
    }

    TId Subscribe(THandler&& handler)
    {
        std::lock_guard<TLock> guard(m_lock);
        return TBase::Subscribe(std::forward<THandler>(handler));
    }

    void Unsubscribe(const TId& id)
    {
        std::lock_guard<TLock> guard(m_lock);
        TBase::Unsubscribe(id);
    }

    void Notify(const TArgs&... args) const
    {
        // copy handlers
        TMap handlers;
        {
            std::shared_lock<TLock> guard(m_lock);
            handlers = TBase::m_handlers;
        }

        // notify
        for (const auto& kvp : handlers)
        {
            const auto& handler = std::get<1>(kvp);
            handler(args...);
        }
    }

protected:

    mutable TLock m_lock;
};