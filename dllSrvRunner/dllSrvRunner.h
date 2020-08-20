#pragma once
#pragma warning(disable:4251)
#include "windows.h"
#include "stdio.h"
#include "string.h"
#include "unordered_map"

#ifdef DLLSRVRUNNER_EXPORTS
#define DLLSRVRUNNER_API _declspec(dllexport)  

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
#define ERROR_SERVICE_DISABLED              1058L
#define ERROR_SERVICE_DOES_NOT_EXIST        1060L
#define ERROR_SERVICE_CANNOT_ACCEPT_CTRL    1061L
#define ERROR_SERVICE_NOT_ACTIVE            1062L
#define ERROR_SERVICE_MARKED_FOR_DELETE     1072L
#define ERROR_SERVICE_EXISTS                1073L
*/

#else
#define DLLSRVRUNNER_API _declspec(dllimport)    
#endif

#define MSG_BUF_SIZE 1024U

extern "C" struct DLLSRVRUNNER_API STATUS
{
    STATUS(DWORD exitCode, PCWSTR msg = TEXT(""));
    BOOL Success = TRUE;
    WCHAR Msg[MSG_BUF_SIZE] = TEXT("");
};

extern "C" class DLLSRVRUNNER_API dllSrvRunner
{
public:
    static STATUS dllOpenSCM();
    static STATUS dllLookup(PWSTR srvName);
    static STATUS dllCreate(PWSTR drvPath, PWSTR srvName);
    static STATUS dllStart(PWSTR srvName);
    static STATUS dllStop(PWSTR srvName);
    static STATUS dllDelete(PWSTR srvName, BOOL force);
    static STATUS dllClear();

private:
    static STATUS   dllOpenSrv(SC_HANDLE& phService, PWSTR srvName);
    static VOID     dllDelHandle(SC_HANDLE& hService);

    static SC_HANDLE                                        hSCManager;
    static std::unordered_map<PWSTR, SC_HANDLE>             hSrvMap;
    static std::unordered_map<PWSTR, SC_HANDLE>::iterator   srvIter;
    static std::unordered_map<DWORD, PCWSTR>                expected_err;
    static std::unordered_map<DWORD, PCWSTR>::iterator      errIter;

    friend inline void AppendErrInf(PWSTR msg, DWORD errCode, PWSTR end);
};