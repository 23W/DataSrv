#include "pch.h"
#include <pdh.h>
#include <pdhmsg.h>
#include <comdef.h>

#include "CPUTempPDHProvider.h"

#pragma comment(lib, "pdh.lib")

// Construction

CCPUTempPDHProvider::CCPUTempPDHProvider()
{
}

CCPUTempPDHProvider::~CCPUTempPDHProvider()
{
    StopThread();
}

// Methods

CCPUTempPDHProvider::TSampleEvent::TId CCPUTempPDHProvider::Subscrive(TSampleEvent::THandler&& handler)
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

void CCPUTempPDHProvider::Unsubscrive(const TSampleEvent::TId& id)
{
    std::lock_guard<TLock> lock(m_lock);

    m_sampleEvent.Unsubscribe(id);

    if (m_sampleEvent.IsEmpty())
    {
        StopThread();
    }
}

// Helper Methods

void CCPUTempPDHProvider::RunThread()
{
    if (m_running)
    {
        return;
    }

    m_thread = std::thread([this]()
    {
        m_running = true;

        PDH_HQUERY hQuery = NULL;
        auto status = PdhOpenQuery(nullptr, 0, &hQuery);
        if (status == ERROR_SUCCESS)
        {
            static const LPCWSTR szCounter = L"\\Thermal Zone Information(*)\\Temperature";

            PDH_HCOUNTER hCounter = NULL;
            status = PdhAddCounter(hQuery, szCounter, 0, &hCounter);
            if (status == ERROR_SUCCESS)
            {
                PdhCollectQueryData(hQuery);

                while (m_running)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));

                    PdhCollectQueryData(hQuery);

                    PDH_FMT_COUNTERVALUE counterVal;
                    status = PdhGetFormattedCounterValue(hCounter, PDH_FMT_DOUBLE, nullptr, &counterVal);
                    if (status == ERROR_SUCCESS)
                    {
                        const auto kelvin = counterVal.doubleValue;
                        const auto celsius = kelvin - 273.15;
                     
                        m_sampleEvent.Notify(static_cast<float>(celsius));
                    }

                }
            }

            PdhCloseQuery(hQuery);
        }
    });
}

void CCPUTempPDHProvider::StopThread()
{
    m_running = false;

    if (m_thread.joinable())
    {
        m_thread.join();
    }
}
