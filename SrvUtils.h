#pragma once
#pragma warning(disable:4251)

#include "windows.h"
#include "stdio.h"
#include "string.h"
#include "unordered_map"
//#include "minwindef.h"
//#include "errhandlingapi.h"
//#include "winerror.h"
//#include "winsvc.h"
//#include "winnt.h"


#define SUCCESS                                0L
#define ERROR_UNKNOWN                      99999L
#define ERROR_NO_MSG                       10001L
#define ERROR_NEED_CONFIRM                 10002L 

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

#define MSG_BUF_SIZE (size_t)1024

namespace DrvLoader
{
    inline void AppendErrInfo(PWSTR msg, DWORD errCode, PWSTR end);

    struct STATUS
    {
        DWORD exitCode;
        WCHAR Msg[MSG_BUF_SIZE] = TEXT("");

        STATUS(DWORD exitCode, OPTIONAL PCWSTR msg);
        BOOL Success() { return exitCode == SUCCESS; }
    };

    class SrvUtils
    {
    public:
        static STATUS OpenSCM();
        static STATUS Lookup(PWSTR srvName);
        static STATUS Create(PWSTR drvPath, PWSTR srvName);
        static STATUS Start(PWSTR srvName);
        static STATUS Stop(PWSTR srvName, OPTIONAL BOOL force = FALSE);
        static STATUS Delete(PWSTR srvName, OPTIONAL BOOL force = FALSE);
        static STATUS Clear();

    private:
        static STATUS   OpenSrv(SC_HANDLE& phService, PWSTR srvName, OPTIONAL ULONG Access);
        static VOID     DelHandle(SC_HANDLE& hService);

        static SC_HANDLE                                        hSCManager;
        static std::unordered_map<PWSTR, SC_HANDLE>             hSrvMap;
        static std::unordered_map<PWSTR, SC_HANDLE>::iterator   srvIter;
        static std::unordered_map<DWORD, PCWSTR>                expected_err;
        static std::unordered_map<DWORD, PCWSTR>::iterator      errIter;

        friend inline void AppendErrInfo(PWSTR msg, DWORD errCode, PWSTR end);
    };
}

