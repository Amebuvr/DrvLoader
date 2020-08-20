#pragma once
#include "windows.h"
#include "exception"
#include "vcclr.h"
#include "../dllSrvRunner/dllSrvRunner.h"

using namespace System;

namespace SrvRunnerCLR {
    public ref class SrvRunner
    {
    public:
        static void OpenSCM();
        static void Create(String^ drvPath, String^ srvName);
        static void Lookup(String^ srvName);
        static void Start(String^ srvName);
        static void Stop(String^ srvName);
        static void Delete(String^ srvName, bool force);
        static void CLear();
    };
}
