#include "pch.h"
#include "dllSrvRunner.h"

#define ThrowToCS(msg) throw msg

std::unordered_map<DWORD, PCWSTR> expected_err = {
   {ERROR_PATH_NOT_FOUND            ,L"找不到服务二进制文件。"},
   {ERROR_ACCESS_DENIED             ,L"拒绝访问。"},
   {ERROR_INVALID_NAME              ,L"指定的服务名无效。"},
   {ERROR_SERVICE_ALREADY_RUNNING   ,L"服务的实例已在运行。"},
   {ERROR_SERVICE_CANNOT_ACCEPT_CTRL,L"服务无法在此时接受控制信息。服务可能已停止/正在停止/正在启动。"},
   {ERROR_SERVICE_NOT_ACTIVE        ,L"服务尚未启动。"},
   {ERROR_SERVICE_MARKED_FOR_DELETE ,L"服务已标记为删除。"},
   {ERROR_SERVICE_EXISTS            ,L"指定的服务已存在。"} };

std::unordered_map<DWORD, PCWSTR>::iterator errIter;

SC_HANDLE hSCManager;
std::unordered_map<WCHAR*, SC_HANDLE> hSrvMap;
std::unordered_map<WCHAR*, SC_HANDLE>::iterator srvIter;

STATUS::STATUS(DWORD exitCode, PCWSTR msg)
{
    if (exitCode == SUCCESS)
    {
        this->Success = TRUE;
    }
    else
    {
        this->Success = FALSE;
        errIter = expected_err.find(exitCode);
        if (errIter != expected_err.end())
        {
            wcscat_s(this->Msg, MSG_BUFF_SIZE, errIter->second);
        }
        else
        {
            wcscat_s(this->Msg, MSG_BUFF_SIZE, L"未知错误。");
        }
    }
    wcscat_s(this->Msg, MSG_BUFF_SIZE, msg);
}

SC_HANDLE dllSrvRunner::dllOpenSrv(WCHAR* srvName)
{
    srvIter = hSrvMap.find(srvName);
    if (srvIter == hSrvMap.end())
    {
        return OpenService(hSCManager, srvName, SERVICE_ALL_ACCESS);
    }
    else
    {
        return srvIter->second;
    }
}

STATUS dllSrvRunner::dllOpenSCM()
{
    hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);

    if (hSCManager == NULL)
    {
        PCWCHAR msg = L"打开服务管理器失败。\r\n";
        return STATUS(GetLastError(), msg);
    }

    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllCreate(WCHAR* drvPath, WCHAR* srvName)
{
    SC_HANDLE hService;

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
        //if (GetLastError() == ERROR_SERVICE_EXISTS)
        //{
        //    srvIter = hSrvMap.find(srvName);
        //    if (srvIter != hSrvMap.end())
        //    {
        //        hService = srvIter->second;
        //    }
        //    else
        //    {
        //        hService = OpenService(hSCManager, srvName, SERVICE_ALL_ACCESS);
        //        hSrvMap.insert(std::make_pair(srvName, hService));
        //    }

        //    if (hService == NULL)
        //    {
        //        ThrowToCS("Service already existed. Open service failed.");
        //    }
        //}
        //else
        //{
        //    ThrowToCS("Create service failed.");
        //}

        return STATUS(GetLastError());
    }

    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllStart(WCHAR* srvName)
{
    SC_HANDLE hService = dllOpenSrv(srvName);

    if (hService == NULL)
    {
        return STATUS(GetLastError(), L"打开服务失败。");
    }

    if (!StartService(hService, NULL, NULL))
    {
        CloseServiceHandle(hService);
        return STATUS(GetLastError(), L"启动失败。");
    }

    CloseServiceHandle(hService);

    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllStop(WCHAR* srvName)
{
    SC_HANDLE hService = dllOpenSrv(srvName);

    SERVICE_STATUS srvStatus = { 0 };

    if (hService == NULL)
    {
        return STATUS(GetLastError(), L"打开服务失败。");
    }

    if (!ControlService(hService, SERVICE_CONTROL_STOP, &srvStatus))
    {
        CloseServiceHandle(hService);
        return STATUS(GetLastError(), L"停止失败。");
    }

    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllDelete(WCHAR* srvName)
{
    SC_HANDLE hService = dllOpenSrv(srvName);

    if (hService == NULL)
    {
        return STATUS(GetLastError(), L"打开服务失败。");
    }

    DeleteService(hService);
    CloseServiceHandle(hService);

    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllEnd()
{
    SERVICE_STATUS srvStatus = { 0 };
    for (srvIter = hSrvMap.begin(); srvIter != hSrvMap.end(); srvIter++)
    {
        ControlService(srvIter->second, SERVICE_CONTROL_STOP, &srvStatus);
        DeleteService(srvIter->second);
        CloseServiceHandle(srvIter->second);
    }
    CloseServiceHandle(hSCManager);
    hSrvMap.clear();

    return STATUS(SUCCESS);
}
