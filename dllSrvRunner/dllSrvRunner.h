#pragma once
#include "windows.h"
#include "stdio.h"
#include "string.h"
#include "unordered_map"
#include "typeinfo"

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
    static STATUS dllLookup(WCHAR* srvName);
    static STATUS dllCreate(WCHAR* drvPath, WCHAR* srvName);
    static STATUS dllStart(WCHAR* srvName);
    static STATUS dllStop(WCHAR* srvName);
    static STATUS dllDelete(WCHAR* srvName);
    static STATUS dllEnd();

private:
    static SC_HANDLE dllOpenSrv(WCHAR* srvName);
};