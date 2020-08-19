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

std::unordered_map<DWORD, PCWSTR> dllSrvRunner::expected_err = {
{ERROR_PATH_NOT_FOUND,            TEXT("找不到服务二进制文件。")},
{ERROR_ACCESS_DENIED,             TEXT("拒绝访问。")},
{ERROR_INVALID_NAME,              TEXT("指定的服务名无效。")},
{ERROR_BAD_EXE_FORMAT,            TEXT("指定的二进制文件无效。")},
{ERROR_SERVICE_ALREADY_RUNNING,   TEXT("服务的实例已在运行。")},
{ERROR_SERVICE_DOES_NOT_EXIST,    TEXT("指定的服务不存在。")},
{ERROR_SERVICE_CANNOT_ACCEPT_CTRL,TEXT("服务无法在此时接受控制信息。服务可能已停止/正在停止/正在启动。")},
{ERROR_SERVICE_NOT_ACTIVE,        TEXT("服务尚未启动。")},
{ERROR_SERVICE_MARKED_FOR_DELETE, TEXT("服务已标记为删除。")},
{ERROR_NO_MSG,                    TEXT("")} };

std::unordered_map<DWORD, PCWSTR>::iterator dllSrvRunner::errIter;

SC_HANDLE dllSrvRunner::hSCManager;
std::unordered_map<PWSTR, SC_HANDLE> dllSrvRunner::hSrvMap;
std::unordered_map<PWSTR, SC_HANDLE>::iterator dllSrvRunner::srvIter;

inline void AppendErrInf(PWSTR msg, DWORD errCode, PWSTR end = TEXT("\r\n"))
{
    dllSrvRunner::errIter = dllSrvRunner::expected_err.find(errCode);
    if (dllSrvRunner::errIter != dllSrvRunner::expected_err.end())
    {
        if (dllSrvRunner::errIter->first != ERROR_NO_MSG)
        {
            wcscat_s(msg, MSG_BUF_SIZE, dllSrvRunner::errIter->second);
            wcscat_s(msg, MSG_BUF_SIZE, end);
        }
    }
    else
    {
        wcscat_s(msg, MSG_BUF_SIZE, TEXT("未知错误。"));
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

STATUS dllSrvRunner::dllOpenSrv(SC_HANDLE& hService, PWSTR srvName)
{
    srvIter = hSrvMap.find(srvName);
    if (srvIter != hSrvMap.end())
    {
        hService = srvIter->second;
        return STATUS(SUCCESS);
    }
    hService = OpenService(hSCManager, srvName, SERVICE_ALL_ACCESS);
    if (hService == NULL)
    {
        return STATUS(GetLastError(), TEXT("打开服务失败，"));
    }
    return STATUS(SUCCESS);
}

VOID dllSrvRunner::dllDelHandle(SC_HANDLE& hService)
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

STATUS dllSrvRunner::dllOpenSCM()
{
    hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);

    if (hSCManager == NULL)
    {
        return STATUS(GetLastError(), TEXT("打开服务管理器失败，"));
    }

    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllLookup(PWSTR srvName)
{
    DWORD errCode;
    SC_HANDLE hService;
    STATUS ret = dllOpenSrv(hService, srvName);
    if (!ret.Success)
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
            dllDelHandle(hService);
            return STATUS(errCode, TEXT("获取信息失败，"));
        }
    }

    DWORD cbBufSize = cbBytesNeeded;
    LPQUERY_SERVICE_CONFIG pSrvConf = (LPQUERY_SERVICE_CONFIG)malloc(cbBufSize);
    if (pSrvConf == NULL || !QueryServiceConfig(hService, pSrvConf, cbBufSize, &cbBytesNeeded))
    {
        return STATUS(GetLastError(), TEXT("获取信息失败，"));
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
            return STATUS(GetLastError(), TEXT("内存分配失败，"));
        }
        pSrvDesc->lpDescription = (LPWSTR)((LPBYTE)&pSrvDesc->lpDescription + sizeof(LPWSTR));
        wcscpy_s(pSrvDesc->lpDescription, 63, L"获取描述失败，");
        AppendErrInf(pSrvDesc->lpDescription, errCode, L"");
    }

    WCHAR srvConf[MSG_BUF_SIZE];
    swprintf_s(srvConf,
        L"服务名称：%ls\r\n"
        L"显示名称：%ls\r\n"
        L"类型：0x%x\r\n"
        L"描述：%ls\r\n"
        L"可执行文件的路径：%ls\r\n"
        L"启动类型：0x%x\r\n"
        L"错误控制：0x%x\r\n"
        L"登录身份：%ls\r\n"
        L"分组：%ls\r\n"
        L"组内标识：%d\r\n"
        L"依赖项：%ls\r\n",
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

STATUS dllSrvRunner::dllCreate(PWSTR drvPath, PWSTR srvName)
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
            wcscpy_s(msg, TEXT("创建服务失败，指定的服务名已被以下服务占用：\r\n"));
            wcsapp(msg, dllLookup(srvName).Msg);
            return STATUS(ERROR_NO_MSG, msg);
        }

        return STATUS(GetLastError());
    }

    hSrvMap.insert(std::make_pair(srvName, hService));

    dllDelHandle(hService);
    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllStart(PWSTR srvName)
{
    SC_HANDLE hService;
    STATUS ret = dllOpenSrv(hService, srvName);
    if (!ret.Success)
    {
        return ret;
    }

    if (!StartService(hService, NULL, NULL))
    {
        dllDelHandle(hService);
        return STATUS(GetLastError(), TEXT("启动失败，"));
    }

    dllDelHandle(hService);
    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllStop(PWSTR srvName)
{
    SC_HANDLE hService;
    STATUS ret = dllOpenSrv(hService, srvName);
    if (!ret.Success)
    {
        return ret;
    }

    SERVICE_STATUS srvStatus = { 0 };

    if (!ControlService(hService, SERVICE_CONTROL_STOP, &srvStatus))
    {
        dllDelHandle(hService);
        return STATUS(GetLastError(), TEXT("停止失败，"));
    }

    dllDelHandle(hService);
    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllDelete(PWSTR srvName)
{
    SC_HANDLE hService;
    STATUS ret = dllOpenSrv(hService, srvName);
    if (!ret.Success)
    {
        return ret;
    }
    if (!DeleteService(hService))
    {
        dllDelHandle(hService);
        return STATUS(GetLastError(), TEXT("删除失败，"));
    }
    if (hSrvMap.find(srvName) != hSrvMap.end())
    {
        hSrvMap.erase(srvName);
    }
    dllDelHandle(hService);
    return STATUS(SUCCESS);
}

STATUS dllSrvRunner::dllClear()
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
