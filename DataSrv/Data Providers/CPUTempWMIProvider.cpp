#include "pch.h"
#include <wbemidl.h>
#include <comdef.h>

#include "CPUTempWMIProvider.h"

#pragma comment(lib, "wbemuuid.lib")


// Construction

CCPUTempWMIProvider::CCPUTempWMIProvider()
{
}

CCPUTempWMIProvider::~CCPUTempWMIProvider()
{
    StopThread();
}

// Methods

CCPUTempWMIProvider::TSampleEvent::TId CCPUTempWMIProvider::Subscrive(TSampleEvent::THandler&& handler)
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

void CCPUTempWMIProvider::Unsubscrive(const TSampleEvent::TId& id)
{
    std::lock_guard<TLock> lock(m_lock);
    
    m_sampleEvent.Unsubscribe(id);

    if (m_sampleEvent.IsEmpty())
    {
        StopThread();
    }
}

// Helper Methods

void CCPUTempWMIProvider::RunThread()
{
    if (m_running)
    {
        return;
    }

    m_thread = std::thread([this]()
    {
        m_running = true;

        ATL::CComPtr<IWbemLocator> spLoc;
        auto hr = spLoc.CoCreateInstance(CLSID_WbemLocator);
        if (SUCCEEDED(hr))
        {
            ATL::CComPtr<IWbemServices> spSvc;
            hr = spLoc->ConnectServer(ATL::CComBSTR(L"ROOT\\WMI"),
                                      nullptr,
                                      nullptr,
                                      nullptr,
                                      0,
                                      nullptr,
                                      nullptr,
                                      &spSvc);
            if (SUCCEEDED(hr))
            {
                hr = CoSetProxyBlanket(spSvc,
                                       RPC_C_AUTHN_WINNT,
                                       RPC_C_AUTHZ_NONE,
                                       nullptr,
                                       RPC_C_AUTHN_LEVEL_CALL,
                                       RPC_C_IMP_LEVEL_IMPERSONATE,
                                       nullptr,
                                       EOAC_NONE);
                if (SUCCEEDED(hr))
                {
                    while (m_running)
                    {
                        ATL::CComPtr<IEnumWbemClassObject> spEnum;
                        hr = spSvc->ExecQuery(ATL::CComBSTR(L"WQL"),
                                              ATL::CComBSTR(L"SELECT * FROM MSAcpi_ThermalZoneTemperature"),
                                              WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                                              nullptr,
                                              &spEnum);
                        if (SUCCEEDED(hr) && !!spEnum)
                        {
                            ATL::CComPtr<IWbemClassObject> spObj;
                            ULONG uReturn = 0;

                            while (SUCCEEDED(spEnum->Next(WBEM_INFINITE, 1, &spObj, &uReturn)) && uReturn)
                            {
                                ATL::CComVariant vData;
                                hr = spObj->Get(L"CurrentTemperature", 0, &vData, nullptr, nullptr);
                                if (SUCCEEDED(hr) && 
                                    vData.vt == VT_I4)
                                {
                                    const auto raw = V_I4(&vData);
                                    const auto celsius = (raw / 10.0f) - 273.15f;
                                    m_sampleEvent.Notify(celsius);
                                }
                                spObj.Release();
                            }
                        }

                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }
                }
            }
        }
    });
}

void CCPUTempWMIProvider::StopThread()
{
    m_running = false;

    if (m_thread.joinable())
    {
        m_thread.join();
    }
}
