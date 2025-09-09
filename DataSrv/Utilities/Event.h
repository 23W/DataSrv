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
    using TLock = std::shared_mutex;
    using TId = size_t;
    using TMap = std::unordered_map<TId, THandler>;

    TId Subscribe(THandler&& handler)
    {
        std::lock_guard<TLock> guard(m_lock);

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
        std::lock_guard<TLock> guard(m_lock);

        m_handlers.erase(id);
    }

    void Notify(TArgs&&... args) const
    {
        // copy handlers
        TMap handlers;
        {
            std::shared_lock<TLock> guard(m_lock);
            handlers = m_handlers;
        }

        // notify
        for (const auto& kvp : handlers)
        {
            const auto& handler = std::get<1>(kvp);
            handler(std::forward<TArgs>(args)...);
        }
    }

private:

    mutable TLock m_lock;
    TMap m_handlers;
    TId m_nextId = 1;
};