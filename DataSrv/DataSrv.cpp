#include "pch.h"
#include "DataSrv.h"
#include "Utilities/StringUtilities.h"
#include "Storage/Data Model/Node.h"

CDataSrvModule _AtlModule;

// Construction

CDataSrvModule::CDataSrvModule()
{
}

// Methods

CDataSrvModule& CDataSrvModule::GetModule()
{
    return _AtlModule;
}

CDataSrvModule::TCpuTemp& CDataSrvModule::GetCPUTempProvide(SourceType sourceType)
{
    switch (sourceType)
    {
    case SourceType::PDH:
        return m_cpuTempPDHProvider;
        break;
    case SourceType::WMI:
        return m_cpuTempWMIProvider;
        break;

    default:
        throw std::invalid_argument(std::format("Unknow data source type: {:d}", static_cast<int>(sourceType)));
    }
}

HRESULT CDataSrvModule::InitializeSecurity() noexcept
{
    const auto hr = CoInitializeSecurity(nullptr,
                                         -1,
                                         nullptr,
                                         nullptr,
                                         RPC_C_AUTHN_LEVEL_DEFAULT, //RPC_C_AUTHN_LEVEL_PKT,
                                         RPC_C_IMP_LEVEL_IMPERSONATE, //RPC_C_IMP_LEVEL_IDENTIFY,
                                         nullptr,
                                         EOAC_NONE,
                                         nullptr);

    LogEvent(CStringUtilities::Format(_T("InitializeSecurity: %ld"), hr));
    return hr;
}

HRESULT CDataSrvModule::RegisterClassObjects(DWORD dwClsContext, DWORD dwFlags) noexcept
{
    const auto hr = TBase::RegisterClassObjects(dwClsContext, dwFlags);
    LogEvent(CStringUtilities::Format(_T("RegisterClassObjects %ld"), hr));
    return hr;
}

HRESULT CDataSrvModule::PreMessageLoop(int nShowCmd) noexcept
{
    const auto hr = TBase::PreMessageLoop(nShowCmd);
    LogEvent(CStringUtilities::Format(_T("PreMessageLoop %ld"), hr));
    return hr;
}

HRESULT CDataSrvModule::PostMessageLoop() noexcept
{
    const auto hr = TBase::PostMessageLoop();
    LogEvent(CStringUtilities::Format(_T("PostMessageLoop %ld"), hr));
    return hr;
}

HRESULT CDataSrvModule::Run(int nShowCmd) noexcept
{
    LogEvent(CStringUtilities::Format(_T("Run start %d"), nShowCmd));
    const auto hr = TBase::Run(nShowCmd);
    LogEvent(CStringUtilities::Format(_T("Run stop %ld"), hr));
    return hr;
}

// Module start point

extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/,
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    const auto res = _AtlModule.WinMain(nShowCmd);
    return res;
}
