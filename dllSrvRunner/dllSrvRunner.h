#pragma once
#pragma warning(disable:4251)
#include "windows.h"
#include "stdio.h"
#include "string.h"
#include "unordered_map"

#ifdef DLLSRVRUNNER_EXPORTS
#define DLLSRVRUNNER_API _declspec(dllexport)    
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
    static STATUS dllDelete(PWSTR srvName);
    static STATUS dllClear();

private:
    static STATUS   dllOpenSrv(SC_HANDLE& phService, PWSTR srvName);
    static VOID     dllDelHandle(SC_HANDLE& hService);

    static SC_HANDLE                                        hSCManager;
    static std::unordered_map<PWSTR, SC_HANDLE>            hSrvMap;
    static std::unordered_map<PWSTR, SC_HANDLE>::iterator  srvIter;
    static std::unordered_map<DWORD, PCWSTR>                expected_err;
    static std::unordered_map<DWORD, PCWSTR>::iterator      errIter;

    friend inline void AppendErrInf(PWSTR msg, DWORD errCode, PWSTR end);
};