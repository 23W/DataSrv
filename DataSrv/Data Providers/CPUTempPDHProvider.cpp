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
}

// Overrides

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
