#include "SrvUtils.h"

using namespace DrvLoader;

std::unordered_map<DWORD, PCWSTR>               SrvUtils::expected_err = {
{ERROR_PATH_NOT_FOUND,              TEXT("�Ҳ�������������ļ���")},
{ERROR_ACCESS_DENIED,               TEXT("�ܾ����ʡ�")},
{ERROR_INVALID_NAME,                TEXT("ָ���ķ�������Ч��")},
{ERROR_BAD_EXE_FORMAT,              TEXT("ָ���Ķ������ļ���Ч��")},
{ERROR_DEPENDENT_SERVICES_RUNNING,  TEXT("�������ڴ˷��������������С�")},
{ERROR_SERVICE_ALREADY_RUNNING,     TEXT("�����ʵ���������С�")},
{ERROR_SERVICE_DISABLED,            TEXT("�����ѱ����á�")},
{ERROR_SERVICE_DOES_NOT_EXIST,      TEXT("ָ���ķ��񲻴��ڡ�")},
{ERROR_SERVICE_CANNOT_ACCEPT_CTRL,  TEXT("�����޷��ڴ�ʱ���ܿ�����Ϣ�����������ֹͣ/����ֹͣ/����������")},
{ERROR_SERVICE_NOT_ACTIVE,          TEXT("������δ������")},
{ERROR_SERVICE_MARKED_FOR_DELETE,   TEXT("�����ѱ��Ϊɾ����")},
{ERROR_NO_MSG,                      TEXT("")} };
std::unordered_map<DWORD, PCWSTR>::iterator     SrvUtils::errIter;
std::unordered_map<PWSTR, SC_HANDLE>            SrvUtils::hSrvMap;
std::unordered_map<PWSTR, SC_HANDLE>::iterator  SrvUtils::srvIter;

SC_HANDLE SrvUtils::hSCManager;

#pragma region wcsapp

template<typename P, typename Q, typename...R>
inline void wcsapp(P p, Q q, R...rs)
{
    static_assert(0, "[wcsapp] Argument type mismatch.");
}

template<size_t __Size, typename...R>
inline void wcsapp(WCHAR(&_Destination)[__Size], PCWSTR _Source, R..._res)
{
    wcscat_s(_Destination, _Source);
    wcsapp(_Destination, _res...);
}

template<size_t __Size, typename...R>
inline void wcsapp(WCHAR(&_Destination)[__Size], PWSTR _Source, R..._res)
{
    wcscat_s(_Destination, _Source);
    wcsapp(_Destination, _res...);
}

template<size_t __Size>
inline void wcsapp(WCHAR(&_Destination)[__Size], PCWSTR _Source)
{
    wcscat_s(_Destination, _Source);
}

template<size_t __Size>
inline void wcsapp(WCHAR(&_Destination)[__Size], PWSTR _Source)
{
    wcscat_s(_Destination, _Source);
}

template<typename...R>
inline void wcsapp(PWSTR(&_Destination), size_t _SizeInWords, PCWSTR _Source, R..._res)
{
    wcscat_s(_Destination, _SizeInWords, _Source);
    wcsapp(_Destination, _SizeInWords - wcslen(_Source), _res...);
}

template<typename...R>
inline void wcsapp(PWSTR(&_Destination), size_t _SizeInWords, PWSTR _Source, R..._res)
{
    wcscat_s(_Destination, _SizeInWords, _Source);
    wcsapp(_Destination, _SizeInWords - wcslen(_Source), _res...);
}

template<>
inline void wcsapp(PWSTR(&_Destination), size_t _SizeInWords, PCWSTR _Source)
{
    wcscat_s(_Destination, _SizeInWords, _Source);
}

template<>
inline void wcsapp(PWSTR(&_Destination), size_t _SizeInWords, PWSTR _Source)
{
    wcscat_s(_Destination, _SizeInWords, _Source);
}

#pragma endregion

inline void DrvLoader::AppendErrInfo(PWSTR msg, DWORD errCode, PWSTR end = TEXT("\r\n"))
{
    SrvUtils::errIter = SrvUtils::expected_err.find(errCode);
    if (SrvUtils::errIter != SrvUtils::expected_err.end())
    {
        if (SrvUtils::errIter->first != ERROR_NO_MSG)
        {
            wcsapp(msg, MSG_BUF_SIZE, SrvUtils::errIter->second, end);
        }
    }
    else
    {
        wcsapp(msg, MSG_BUF_SIZE, TEXT("δ֪����"), end);
    }
}

STATUS::STATUS(DWORD exitCode, OPTIONAL PCWSTR msg = TEXT(""))
{
    this->exitCode = exitCode;
    wcscpy_s(this->Msg, msg);
    if (!this->Success())
    {
        AppendErrInfo(this->Msg, exitCode);
    }
}

STATUS SrvUtils::OpenSrv(SC_HANDLE& hService, PWSTR srvName, OPTIONAL ULONG Access = SERVICE_ALL_ACCESS)
{
    srvIter = hSrvMap.find(srvName);
    if (srvIter != hSrvMap.end())
    {
        hService = srvIter->second;
        return STATUS(SUCCESS);
    }
    hService = OpenService(hSCManager, srvName, Access);
    if (hService == NULL)
    {
        return STATUS(GetLastError(), TEXT("�򿪷���ʧ�ܣ�"));
    }
    return STATUS(SUCCESS);
}

VOID SrvUtils::DelHandle(SC_HANDLE& hService)
{
    for (srvIter = hSrvMap.begin(); srvIter != hSrvMap.end(); srvIter++)
    {
        if (srvIter->second == hService)
        {
            return;
        }
    }
    CloseServiceHandle(hService);
}

STATUS SrvUtils::OpenSCM()
{
    hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);

    if (hSCManager == NULL)
    {
        return STATUS(GetLastError(), TEXT("�򿪷��������ʧ�ܣ�"));
    }

    return STATUS(SUCCESS);
}

STATUS SrvUtils::Lookup(PWSTR srvName)
{
    DWORD errCode;
    SC_HANDLE hService;
    STATUS ret = OpenSrv(hService, srvName, SERVICE_QUERY_CONFIG | SERVICE_QUERY_STATUS);
    if (!ret.Success())
    {
        return ret;
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
            DelHandle(hService);
            return STATUS(errCode, TEXT("��ȡ��Ϣʧ�ܣ�"));
        }
    }

    DWORD cbBufSize = cbBytesNeeded;
    LPQUERY_SERVICE_CONFIG pSrvConf = (LPQUERY_SERVICE_CONFIG)malloc(cbBufSize);
    if (pSrvConf == NULL)
    {
        return STATUS(ERROR_UNKNOWN, TEXT("��ȡ��Ϣʱ�ڴ�����ʧ�ܣ�"));
    }

    if (!QueryServiceConfig(hService, pSrvConf, cbBufSize, &cbBytesNeeded))
    {
        free(pSrvConf);
        return STATUS(GetLastError(), TEXT("��ȡ��Ϣʧ�ܣ�"));
    }

    WCHAR errMsg[64];
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
            wcscpy_s(errMsg, TEXT("��ȡ����ʧ�ܣ�"));
            goto SET_DESC_FAILED_MSG;
        }
    }

    cbBufSize = cbBytesNeeded;
    LPSERVICE_DESCRIPTION pSrvDesc = (LPSERVICE_DESCRIPTION)malloc(cbBufSize);
    if (pSrvDesc == NULL)
    {
        errCode = ERROR_UNKNOWN;
        wcscpy_s(errMsg, TEXT("��ȡ������Ϣʱ�ڴ�����ʧ�ܣ�"));
        goto SET_DESC_FAILED_MSG;
    }

    if (
        !QueryServiceConfig2(
            hService,
            SERVICE_CONFIG_DESCRIPTION,
            (LPBYTE)pSrvDesc,
            cbBufSize,
            &cbBytesNeeded))
    {
        errCode = GetLastError();
        free(pSrvDesc);
        wcscpy_s(errMsg, TEXT("��ȡ����ʧ�ܣ�"));
        goto SET_DESC_FAILED_MSG;
    }

    if (0)
    {
    SET_DESC_FAILED_MSG:
        pSrvDesc = (LPSERVICE_DESCRIPTION)malloc(64 * sizeof(WCHAR));
        pSrvDesc->lpDescription = (LPWSTR)(&pSrvDesc->lpDescription + 1);
        wcscpy_s(pSrvDesc->lpDescription, 63, errMsg);
        AppendErrInfo(pSrvDesc->lpDescription, errCode, TEXT(""));
    }

    if (
        !QueryServiceStatusEx(
            hService,
            SC_STATUS_PROCESS_INFO,
            NULL,
            0,
            &cbBytesNeeded))
    {
        errCode = GetLastError();
        if (errCode != ERROR_INSUFFICIENT_BUFFER)
        {
            wcscpy_s(errMsg, TEXT("��ȡ״̬ʧ�ܣ�"));
            goto SET_STATUS_FAILED_MSG;
        }
    }

    cbBufSize = cbBytesNeeded;
    LPSERVICE_STATUS_PROCESS pSrvStatus = (LPSERVICE_STATUS_PROCESS)malloc(cbBufSize);
    if (pSrvStatus == NULL)
    {
        errCode = ERROR_UNKNOWN;
        wcscpy_s(errMsg, TEXT("��ȡ״̬��Ϣʱ�ڴ�����ʧ�ܣ�"));
        goto SET_STATUS_FAILED_MSG;
    }

    if (
        !QueryServiceStatusEx(
            hService,
            SC_STATUS_PROCESS_INFO,
            (LPBYTE)pSrvStatus,
            cbBufSize,
            &cbBytesNeeded))
    {
        errCode = GetLastError();
        free(pSrvStatus);
        wcscpy_s(errMsg, TEXT("��ȡ״̬ʧ�ܣ�"));
        goto SET_DESC_FAILED_MSG;
    }

    if (0)
    {
    SET_STATUS_FAILED_MSG:
        pSrvStatus = (LPSERVICE_STATUS_PROCESS)malloc(sizeof(SERVICE_STATUS_PROCESS));
        pSrvStatus->dwCurrentState = 0;
        pSrvStatus->dwProcessId = 0;
        AppendErrInfo(errMsg, errCode, TEXT(""));
    }

    WCHAR srvConf[MSG_BUF_SIZE];
    LPSTR lpServiceType, lpStartType, lpErrorControl;
    LPWSTR lpCurrentState;

    switch (pSrvConf->dwServiceType)
    {
    case SERVICE_FILE_SYSTEM_DRIVER:
        lpServiceType = "SERVICE_FILE_SYSTEM_DRIVER";
        break;
    case SERVICE_KERNEL_DRIVER:
        lpServiceType = "SERVICE_KERNEL_DRIVER";
        break;
    case SERVICE_WIN32_OWN_PROCESS:
        lpServiceType = "SERVICE_WIN32_OWN_PROCESS";
        break;
    case SERVICE_WIN32_SHARE_PROCESS:
        lpServiceType = "SERVICE_WIN32_SHARE_PROCESS";
        break;
    case SERVICE_INTERACTIVE_PROCESS:
        lpServiceType = "SERVICE_INTERACTIVE_PROCESS";
        break;
    default:
        lpServiceType = "UNKNOWN";
        break;
    }
    switch (pSrvConf->dwStartType)
    {
    case SERVICE_AUTO_START:
        lpStartType = "SERVICE_AUTO_START";
        break;
    case SERVICE_BOOT_START:
        lpStartType = "SERVICE_BOOT_START";
        break;
    case SERVICE_DEMAND_START:
        lpStartType = "SERVICE_DEMAND_START";
        break;
    case SERVICE_DISABLED:
        lpStartType = "SERVICE_DISABLED";
        break;
    case SERVICE_SYSTEM_START:
        lpStartType = "SERVICE_SYSTEM_START";
        break;
    default:
        lpStartType = "";
        break;
    }
    switch (pSrvConf->dwErrorControl)
    {
    case SERVICE_ERROR_CRITICAL:
        lpErrorControl = "SERVICE_ERROR_CRITICAL";
        break;
    case SERVICE_ERROR_IGNORE:
        lpErrorControl = "SERVICE_ERROR_IGNORE";
        break;
    case SERVICE_ERROR_NORMAL:
        lpErrorControl = "SERVICE_ERROR_NORMAL";
        break;
    case SERVICE_ERROR_SEVERE:
        lpErrorControl = "SERVICE_ERROR_SEVERE";
        break;
    default:
        lpErrorControl = "";
        break;
    }
    switch (pSrvStatus->dwCurrentState)
    {
    case SERVICE_CONTINUE_PENDING:
        lpCurrentState = TEXT("���ڻָ�");
        break;
    case SERVICE_PAUSE_PENDING:
        lpCurrentState = TEXT("������ͣ");
        break;
    case SERVICE_PAUSED:
        lpCurrentState = TEXT("����ͣ");
        break;
    case SERVICE_RUNNING:
        lpCurrentState = TEXT("��������");
        break;
    case SERVICE_START_PENDING:
        lpCurrentState = TEXT("��������");
        break;
    case SERVICE_STOP_PENDING:
        lpCurrentState = TEXT("����ֹͣ");
        break;
    case SERVICE_STOPPED:
        lpCurrentState = TEXT("��ֹͣ");
        break;
    default:
        lpCurrentState = errMsg;
        break;
    }

    for (PWCHAR ptr = pSrvConf->lpDependencies; ptr < pSrvConf->lpServiceStartName; ptr++)
    {
        if (*ptr == L'\0')
        {
            if (*(ptr + 1) != L'\0')
            {
                *ptr = L',';
            }
            else
            {
                break;
            }
        }
    }

    swprintf_s(
        srvConf,
        L"�������ƣ�%ls\r\n"
        L"��ʾ���ƣ�%ls\r\n"
        L"���ͣ�%hs\r\n"
        L"������%ls\r\n"
        L"��ִ���ļ���·����%ls\r\n"
        L"�������ͣ�%hs\r\n"
        L"״̬��%ls\r\n"
        L"PID��%d%hs\r\n"
        L"������ƣ�%hs\r\n"
        L"��¼��ݣ�%ls\r\n"
        L"���飺%ls\r\n"
        L"���ڱ�ʶ��%d%hs\r\n"
        L"�����%ls\r\n",
        srvName,
        pSrvConf->lpDisplayName,
        lpServiceType,
        pSrvDesc->lpDescription == NULL ? L"" : pSrvDesc->lpDescription,
        pSrvConf->lpBinaryPathName,
        lpStartType,
        lpCurrentState,
        pSrvStatus->dwProcessId,
        pSrvStatus->dwProcessId == 0 ? " (N/A)" : "",
        lpErrorControl,
        pSrvConf->lpServiceStartName,
        pSrvConf->lpLoadOrderGroup == NULL ? L"" : pSrvConf->lpLoadOrderGroup,
        pSrvConf->dwTagId,
        pSrvConf->lpLoadOrderGroup == NULL ? " (N/A)" : "",
        pSrvConf->lpDependencies == NULL ? L"" : pSrvConf->lpDependencies);

    return STATUS(SUCCESS, srvConf);
}

STATUS SrvUtils::Create(PWSTR drvPath, PWSTR srvName)
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
            wcsapp(msg, Lookup(srvName).Msg);
            return STATUS(ERROR_NO_MSG, msg);
        }

        return STATUS(GetLastError());
    }

    hSrvMap.insert(std::make_pair(srvName, hService));

    DelHandle(hService);
    return STATUS(SUCCESS);
}

STATUS SrvUtils::Start(PWSTR srvName)
{
    SC_HANDLE hService;
    STATUS ret = OpenSrv(hService, srvName, SERVICE_START);
    if (!ret.Success())
    {
        return ret;
    }

    if (!StartService(hService, NULL, NULL))
    {
        DelHandle(hService);
        return STATUS(GetLastError(), TEXT("����ʧ�ܣ�"));
    }

    DelHandle(hService);
    return STATUS(SUCCESS);
}

STATUS SrvUtils::Stop(PWSTR srvName, OPTIONAL BOOL force)
{
    SC_HANDLE hService;
    STATUS ret = OpenSrv(hService, srvName, SERVICE_STOP);
    if (!ret.Success())
    {
        return ret;
    }

    SERVICE_STATUS srvStatus = { 0 };

    if (!ControlService(hService, SERVICE_CONTROL_STOP, &srvStatus))
    {
        DelHandle(hService);
        return STATUS(GetLastError(), TEXT("ֹͣʧ�ܣ�"));
    }

    DelHandle(hService);
    return STATUS(SUCCESS);
}

STATUS SrvUtils::Delete(PWSTR srvName, OPTIONAL BOOL force)
{
    SC_HANDLE hService;
    STATUS ret = OpenSrv(hService, srvName, DELETE);
    if (!ret.Success())
    {
        return ret;
    }

    if (!force && hSrvMap.find(srvName) == hSrvMap.end())
    {
        return STATUS(ERROR_NEED_CONFIRM, TEXT("ɾ��������Ҫȷ�ϡ�"));
    }

    if (!DeleteService(hService))
    {
        DelHandle(hService);
        return STATUS(GetLastError(), TEXT("ɾ��ʧ�ܣ�"));
    }
    if (hSrvMap.find(srvName) != hSrvMap.end())
    {
        hSrvMap.erase(srvName);
    }
    DelHandle(hService);
    return STATUS(SUCCESS);
}

STATUS SrvUtils::Clear()
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
