#pragma once

#include <atomic>
#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

#include "..\Utilities\Event.h"

// Forward declarations;
struct IDXCoreAdapter;

class CGPUTempProvider
{
public:
    using TSampleEvent = Event<float>;
    using TLock = std::mutex;

    class CAdapter
    {
    public:
        CAdapter(ATL::CComPtr<IDXCoreAdapter>&& spAdapter) noexcept;
        CAdapter(CAdapter&& adapter) noexcept;
        ~CAdapter();

        CAdapter& operator = (CAdapter&& adapter) noexcept;

        ATL::CStringW GetDescription();

    private:

        ATL::CComPtr<IDXCoreAdapter> m_spAdapter;
    };

    // Construction

    CGPUTempProvider();
    virtual ~CGPUTempProvider();

    // Methods

    size_t GetAdapterCount() { Init(); return m_adapters.size(); }
    CAdapter& GetAdapter(size_t index) { return m_adapters[index]; }

protected:

    // Helper Methods

    void Init();

    // Members

    std::vector<CAdapter> m_adapters;
    bool m_initialized;

    // Deleted methods

    CGPUTempProvider(const CGPUTempProvider&) = delete;
    CGPUTempProvider(CGPUTempProvider&&) = delete;
    CGPUTempProvider& operator = (const CGPUTempProvider&) = delete;
    CGPUTempProvider& operator = (CGPUTempProvider&&) = delete;
};
