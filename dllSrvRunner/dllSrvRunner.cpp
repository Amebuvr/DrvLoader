#include "pch.h"
#include "dllSrvRunner.h"
#include "stdio.h"

#define ThrowToCS(msg) throw gcnew System::Exception(gcnew System::String(msg))

void Create(WCHAR* drvPath, WCHAR* srvName)
{
    hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (hSCManager == NULL)
    {
        ThrowToCS("Open SCManager Failed.");
    }

    hService = CreateService(
        hSCManager,
        srvName,
        srvName,
        SERVICE_ALL_ACCESS,
        SERVICE_KERNEL_DRIVER,
        SERVICE_DEMAND_START,
        SERVICE_ERROR_IGNORE,
        drvPath,
        NULL, NULL, NULL, NULL, NULL);

    if (hService == NULL)
    {
        if (GetLastError() == ERROR_SERVICE_EXISTS)
        {
            hService = OpenService(hSCManager, srvName, SERVICE_ALL_ACCESS);

            if (hService == NULL)
            {
                ThrowToCS("Service already existed. Open service failed.");
            }
        }
        else
        {
            ThrowToCS("Create service failed.");
        }
    }
}

void Start()
{
    if (!StartService(hService, NULL, NULL))
    {
        ThrowToCS("Start service failed.");
    }
}

void Stop()
{
    SERVICE_STATUS srvStatus = { 0 };
    if (!ControlService(hService, SERVICE_CONTROL_STOP, &srvStatus))
    {
        ThrowToCS("Stop service failed.");
    }
}

void Delete()
{
    DeleteService(hService);
    CloseHandle(hService);
    CloseHandle(hSCManager);
}