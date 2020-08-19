#include "pch.h"
#include "dllSrvRunner.h"

#define ThrowToCS(msg) throw msg

#define SUCCESS                                0L
#define ERROR_UNKNOWN                      99999L
#define ERROR_NO_MSG                       10001L

/*
* * Already defined in winerror.h
**
#define ERROR_PATH_NOT_FOUND                   3L
#define ERROR_ACCESS_DENIED                    5L
#define ERROR_INVALID_NAME                   123L
#define ERROR_BAD_EXE_FORMAT                 193L
#define ERROR_SERVICE_ALREADY_RUNNING       1056L
#define ERROR_SERVICE_DOES_NOT_EXIST        1060L
#define ERROR_SERVICE_CANNOT_ACCEPT_CTRL    1061L
#define ERROR_SERVICE_NOT_ACTIVE            1062L
#define ERROR_SERVICE_MARKED_FOR_DELETE     1072L
#define ERROR_SERVICE_EXISTS                1073L
*/

static std::unordered_map<DWORD, PCWSTR> expected_err = {
{ERROR_PATH_NOT_FOUND,            TEXT("�Ҳ�������������ļ���")},
{ERROR_ACCESS_DENIED,             TEXT("�ܾ����ʡ�")},
{ERROR_INVALID_NAME,              TEXT("ָ���ķ�������Ч��")},
{ERROR_BAD_EXE_FORMAT,            TEXT("ָ���Ķ������ļ���Ч��")},
{ERROR_SERVICE_ALREADY_RUNNING,   TEXT("�����ʵ���������С�")},
{ERROR_SERVICE_DOES_NOT_EXIST,    TEXT("ָ���ķ��񲻴��ڡ�")},
{ERROR_SERVICE_CANNOT_ACCEPT_CTRL,TEXT("�����޷��ڴ�ʱ���ܿ�����Ϣ�����������ֹͣ/����ֹͣ/����������")},
{ERROR_SERVICE_NOT_ACTIVE,        TEXT("������δ������")},
{ERROR_SERVICE_MARKED_FOR_DELETE, TEXT("�����ѱ��Ϊɾ����")},
{ERROR_NO_MSG,                    TEXT("")} };

static std::unordered_map<DWORD, PCWSTR>::iterator errIter;

static SC_HANDLE hSCManager;
static std::unordered_map<WCHAR*, SC_HANDLE> hSrvMap;
static std::unordered_map<WCHAR*, SC_HANDLE>::iterator srvIter;

inline void AppendErrInf(PWSTR msg, DWORD errCode, PWSTR end = TEXT("\r\n"))
{
    errIter = expected_err.find(errCode);
    if (errIter != expected_err.end())
    {
        if (errIter->first != ERROR_NO_MSG)
        {
            wcscat_s(msg, MSG_BUF_SIZE, errIter->second);
            wcscat_s(msg, MSG_BUF_SIZE, end);
        }
    }
    else
    {
        wcscat_s(msg, MSG_BUF_SIZE, TEXT("δ֪����"));
        wcscat_s(msg, MSG_BUF_SIZE, end);
    }
}

#pragma region wcsapp

template<size_t __Size, typename P, typename...Q>
inline void wcsapp(WCHAR(&_Destination)[__Size], P _Source, Q..._res)
{
    static_assert(0, "[wcsapp] Argument type mismatch.");
}

template<size_t __Size, typename...Q>
inline void wcsapp(WCHAR(&_Destination)[__Size], PWCHAR _Source, Q..._res)
{
    wcscat_s(_Destination, _Source);
    wcsapp(_Destination, _res...);
}

template<size_t __Size, typename...Q>
inline void wcsapp(WCHAR(&_Destination)[__Size], PCWCHAR _Source, Q..._res)
{
    wcscat_s(_Destination, _Source);
    wcsapp(_Destination, _res...);
}

template<size_t __Size, typename P>
inline void wcsapp(WCHAR(&_Destination)[__Size], P _Source)
{
    static_assert(0, "[wcsapp] Argument type mismatch.");
}

template<size_t __Size>
inline void wcsapp(WCHAR(&_Destination)[__Size], PWCHAR _Source)
{
    wcscat_s(_Destination, _Source);
}

template<size_t __Size>
inline void wcsapp(WCHAR(&_Destination)[__Size], PCWCHAR _Source)
{
    wcscat_s(_Destination, _Source);
}

#pragma endregion

STATUS::STATUS(DWORD exitCode, PCWSTR msg)
{
    wcsapp(this->Msg, msg);
    if (exitCode == SUCCESS)
    {
        this->Success = TRUE;
    }
    else
    {
        this->Success = FALSE;
        AppendErrInf(this->Msg, exitCode);
    }
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
        return STATUS(GetLastError(), TEXT("�򿪷��������ʧ�ܣ�"));
    }

    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllLookup(WCHAR* srvName)
{
    DWORD errCode;

    SC_HANDLE hService = OpenService(hSCManager, srvName, SERVICE_ALL_ACCESS);
    if (hService == NULL)
    {
        return STATUS(GetLastError(), TEXT("�򿪷���ʧ�ܣ�"));
    }

    DWORD  cbBytesNeeded = 0L;
    if (
        !QueryServiceConfig(
            hService,
            NULL,
            0,
            &cbBytesNeeded))
    {
        errCode = GetLastError();
        if (errCode != ERROR_INSUFFICIENT_BUFFER)
        {
            CloseServiceHandle(hService);
            return STATUS(errCode, TEXT("��ȡ��Ϣʧ�ܣ�"));
        }
    }

    DWORD cbBufSize = cbBytesNeeded;
    LPQUERY_SERVICE_CONFIG pSrvConf = (LPQUERY_SERVICE_CONFIG)malloc(cbBufSize);
    if (pSrvConf == NULL || !QueryServiceConfig(hService, pSrvConf, cbBufSize, &cbBytesNeeded))
    {
        return STATUS(GetLastError(), TEXT("��ȡ��Ϣʧ�ܣ�"));
    }

    LPSERVICE_DESCRIPTION pSrvDesc;
    if (
        !QueryServiceConfig2(
            hService,
            SERVICE_CONFIG_DESCRIPTION,
            NULL,
            0,
            &cbBytesNeeded))
    {
        errCode = GetLastError();
        if (errCode != ERROR_INSUFFICIENT_BUFFER)
        {
            goto SET_FAILED_MSG;
        }
    }

    cbBufSize = cbBytesNeeded;
    pSrvDesc = (LPSERVICE_DESCRIPTION)malloc(cbBufSize);

    if (pSrvDesc == NULL
        || !QueryServiceConfig2(
            hService,
            SERVICE_CONFIG_DESCRIPTION,
            (LPBYTE)pSrvDesc,
            cbBufSize,
            &cbBytesNeeded))
    {
        errCode = GetLastError();
        free(pSrvDesc);
        goto SET_FAILED_MSG;
    }

    if (0)
    {
    SET_FAILED_MSG:
        pSrvDesc = (LPSERVICE_DESCRIPTION)malloc(64 * sizeof(WCHAR));
        if (pSrvDesc == NULL)
        {
            return STATUS(GetLastError(), TEXT("�ڴ����ʧ�ܣ�"));
        }
        pSrvDesc->lpDescription = (LPWSTR)((LPBYTE)&pSrvDesc->lpDescription + sizeof(LPWSTR));
        wcscpy_s(pSrvDesc->lpDescription, 63, L"��ȡ����ʧ�ܣ�");
        AppendErrInf(pSrvDesc->lpDescription, errCode, L"");
    }

    WCHAR srvConf[MSG_BUF_SIZE];
    swprintf_s(srvConf,
        L"�������ƣ�%ls\r\n"
        L"��ʾ���ƣ�%ls\r\n"
        L"���ͣ�0x%x\r\n"
        L"������%ls\r\n"
        L"��ִ���ļ���·����%ls\r\n"
        L"�������ͣ�0x%x\r\n"
        L"������ƣ�0x%x\r\n"
        L"��¼��ݣ�%ls\r\n"
        L"���飺%ls\r\n"
        L"���ڱ�ʶ��%d\r\n"
        L"�����%ls\r\n",
        srvName,
        pSrvConf->lpDisplayName,
        pSrvConf->dwServiceType,
        pSrvDesc->lpDescription == NULL ? L"" : pSrvDesc->lpDescription,
        pSrvConf->lpBinaryPathName,
        pSrvConf->dwStartType,
        pSrvConf->dwErrorControl,
        pSrvConf->lpServiceStartName,
        pSrvConf->lpLoadOrderGroup == NULL ? L"" : pSrvConf->lpLoadOrderGroup,
        pSrvConf->dwTagId,
        pSrvConf->lpDependencies == NULL ? L"" : pSrvConf->lpDependencies);

    return STATUS(SUCCESS, srvConf);
}

STATUS dllSrvRunner::dllCreate(WCHAR* drvPath, WCHAR* srvName)
{
    SC_HANDLE hService;

    hService =
        CreateService(
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
        DWORD errCode = GetLastError();
        WCHAR msg[MSG_BUF_SIZE];

        if (errCode == ERROR_SERVICE_EXISTS)
        {
            wcscpy_s(msg, TEXT("��������ʧ�ܣ�ָ���ķ������ѱ����·���ռ�ã�\r\n"));
            wcsapp(msg, dllLookup(srvName).Msg);
            return STATUS(ERROR_NO_MSG, msg);
        }

        return STATUS(GetLastError());
    }

    hSrvMap.insert(std::make_pair(srvName, hService));

    CloseServiceHandle(hService);
    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllStart(WCHAR* srvName)
{
    SC_HANDLE hService = dllOpenSrv(srvName);

    if (hService == NULL)
    {
        return STATUS(GetLastError(), TEXT("�򿪷���ʧ�ܣ�"));
    }

    if (!StartService(hService, NULL, NULL))
    {
        CloseServiceHandle(hService);
        return STATUS(GetLastError(), TEXT("����ʧ�ܣ�"));
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
        return STATUS(GetLastError(), TEXT("�򿪷���ʧ�ܣ�"));
    }

    if (!ControlService(hService, SERVICE_CONTROL_STOP, &srvStatus))
    {
        CloseServiceHandle(hService);
        return STATUS(GetLastError(), TEXT("ֹͣʧ�ܣ�"));
    }

    CloseServiceHandle(hService);
    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllDelete(WCHAR* srvName)
{
    SC_HANDLE hService = dllOpenSrv(srvName);

    if (hService == NULL)
    {
        return STATUS(GetLastError(), TEXT("�򿪷���ʧ�ܣ�"));
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
