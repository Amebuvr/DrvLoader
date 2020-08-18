#include "pch.h"

#include "SrvRunnerCLR.h"

#define ThrowToCS(msg) throw gcnew System::Exception(gcnew System::String(msg))

void SrvRunnerCLR::SrvRunner::OpenSCM()
{
    STATUS& ret = dllSrvRunner::dllOpenSCM();
    if (!ret.Success)
    {
        ThrowToCS(ret.Msg);
    }
}

void SrvRunnerCLR::SrvRunner::Create(String^ drvPath, String^ srvName)
{
    pin_ptr<const WCHAR> path = PtrToStringChars(drvPath);
    pin_ptr<const WCHAR> name = PtrToStringChars(srvName);
    STATUS& ret = dllSrvRunner::dllCreate((WCHAR*)path, (WCHAR*)name);
    if (!ret.Success)
    {
        ThrowToCS(ret.Msg);
    }
}

void SrvRunnerCLR::SrvRunner::Start(String^ srvName)
{
    pin_ptr<const WCHAR> name = PtrToStringChars(srvName);
    STATUS& ret = dllSrvRunner::dllStart((WCHAR*)name);
    if (!ret.Success)
    {
        ThrowToCS(ret.Msg);
    }
}

void SrvRunnerCLR::SrvRunner::Stop(String^ srvName)
{
    pin_ptr<const WCHAR> name = PtrToStringChars(srvName);
    STATUS& ret = dllSrvRunner::dllStop((WCHAR*)name);
    if (!ret.Success)
    {
        ThrowToCS(ret.Msg);
    }
}

void SrvRunnerCLR::SrvRunner::Delete(String^ srvName)
{
    pin_ptr<const WCHAR> name = PtrToStringChars(srvName);
    STATUS& ret = dllSrvRunner::dllDelete((WCHAR*)name);
    if (!ret.Success)
    {
        ThrowToCS(ret.Msg);
    }
}

void SrvRunnerCLR::SrvRunner::End()
{
    STATUS& ret = dllSrvRunner::dllEnd();
    if (!ret.Success)
    {
        ThrowToCS(ret.Msg);
    }
}
