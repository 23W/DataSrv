#pragma once

#include "framework.h"
#include "resource.h"
#include "COM/DataSrv_i.h"
#include "Data Providers/CPUTempWMIProvider.h"

using namespace ATL;

class CDataSrvModule : public ATL::CAtlServiceModuleT< CDataSrvModule, IDS_SERVICENAME >
{
public:
    using TBase = ATL::CAtlServiceModuleT< CDataSrvModule, IDS_SERVICENAME >;
    using TCpuTemp = CCPUTempWMIProvider;

    DECLARE_LIBID(LIBID_DataSrvLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DATASRV, "{91a7732c-78ba-49c0-a70b-72775c343a6f}")

    static CDataSrvModule& GetModule();

    TCpuTemp& GetCPUTempProvide() { return m_cpuTempProvider; }

    HRESULT InitializeSecurity() noexcept;
    HRESULT RegisterClassObjects(DWORD dwClsContext, DWORD dwFlags) noexcept;

    HRESULT PreMessageLoop(int nShowCmd) noexcept;
    HRESULT PostMessageLoop() noexcept;
    HRESULT Run(int nShowCmd) noexcept;

private:
    TCpuTemp m_cpuTempProvider;
};