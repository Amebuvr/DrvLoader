#pragma once
#include "windows.h"
#include "stdio.h"
#include "string.h"
#include "unordered_map"

#ifdef DLLSRVRUNNER_EXPORTS
#define DLLSRVRUNNER_API _declspec(dllexport)    
#else
#define DLLSRVRUNNER_API _declspec(dllimport)    
#endif

#define MSG_BUFF_SIZE 1024U

#define SUCCESS                                0L
#define ERROR_UNKNOWN                          1L

/*
* * Already defined in winerror.h
**
#define ERROR_PATH_NOT_FOUND                   3L
#define ERROR_ACCESS_DENIED                    5L
#define ERROR_INVALID_NAME                   123L
#define ERROR_SERVICE_ALREADY_RUNNING       1056L
#define ERROR_SERVICE_CANNOT_ACCEPT_CTRL    1061L
#define ERROR_SERVICE_NOT_ACTIVE            1062L
#define ERROR_SERVICE_MARKED_FOR_DELETE     1072L
#define ERROR_SERVICE_EXISTS                1073L
*/

extern "C" struct DLLSRVRUNNER_API STATUS
{
    STATUS(DWORD exitCode = SUCCESS, PCWSTR msg = L"");
    BOOL Success = TRUE;
    WCHAR Msg[MSG_BUFF_SIZE] = L"";
};

extern "C" class DLLSRVRUNNER_API dllSrvRunner
{
public:
    static STATUS dllOpenSCM();
    static STATUS dllCreate(WCHAR* drvPath, WCHAR* srvName);
    static STATUS dllStart(WCHAR* srvName);
    static STATUS dllStop(WCHAR* srvName);
    static STATUS dllDelete(WCHAR* srvName);
    static STATUS dllEnd();

private:
    static SC_HANDLE dllOpenSrv(WCHAR* srvName);
};