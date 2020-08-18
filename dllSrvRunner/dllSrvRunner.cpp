#include "pch.h"
#include "dllSrvRunner.h"

#define ThrowToCS(msg) throw msg

std::unordered_map<DWORD, PCWSTR> expected_err = {
   {ERROR_PATH_NOT_FOUND            ,L"�Ҳ�������������ļ���"},
   {ERROR_ACCESS_DENIED             ,L"�ܾ����ʡ�"},
   {ERROR_INVALID_NAME              ,L"ָ���ķ�������Ч��"},
   {ERROR_SERVICE_ALREADY_RUNNING   ,L"�����ʵ���������С�"},
   {ERROR_SERVICE_CANNOT_ACCEPT_CTRL,L"�����޷��ڴ�ʱ���ܿ�����Ϣ�����������ֹͣ/����ֹͣ/����������"},
   {ERROR_SERVICE_NOT_ACTIVE        ,L"������δ������"},
   {ERROR_SERVICE_MARKED_FOR_DELETE ,L"�����ѱ��Ϊɾ����"},
   {ERROR_SERVICE_EXISTS            ,L"ָ���ķ����Ѵ��ڡ�"} };

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
            wcscat_s(this->Msg, MSG_BUFF_SIZE, L"δ֪����");
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
        PCWCHAR msg = L"�򿪷��������ʧ�ܡ�\r\n";
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
        return STATUS(GetLastError(), L"�򿪷���ʧ�ܡ�");
    }

    if (!StartService(hService, NULL, NULL))
    {
        CloseServiceHandle(hService);
        return STATUS(GetLastError(), L"����ʧ�ܡ�");
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
        return STATUS(GetLastError(), L"�򿪷���ʧ�ܡ�");
    }

    if (!ControlService(hService, SERVICE_CONTROL_STOP, &srvStatus))
    {
        CloseServiceHandle(hService);
        return STATUS(GetLastError(), L"ֹͣʧ�ܡ�");
    }

    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllDelete(WCHAR* srvName)
{
    SC_HANDLE hService = dllOpenSrv(srvName);

    if (hService == NULL)
    {
        return STATUS(GetLastError(), L"�򿪷���ʧ�ܡ�");
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
