#include "pch.h"

#include "SrvRunnerCLR.h"

#define ThrowToCS(msg)  throw gcnew System::SystemException(gcnew System::String(msg))
#define MsgToCS(msg)    throw gcnew System::ApplicationException(gcnew System::String(msg))

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

void SrvRunnerCLR::SrvRunner::Lookup(String^ srvName)
{
    pin_ptr<const WCHAR> name = PtrToStringChars(srvName);
    STATUS& ret = dllSrvRunner::dllLookup((WCHAR*)name);
    if (!ret.Success)
    {
        ThrowToCS(ret.Msg);
    }
    else
    {
        MsgToCS(ret.Msg);
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

void SrvRunnerCLR::SrvRunner::Delete(String^ srvName, bool force)
{
    pin_ptr<const WCHAR> name = PtrToStringChars(srvName);
    STATUS& ret = dllSrvRunner::dllDelete((WCHAR*)name, force ? TRUE : FALSE);
    if (!ret.Success)
    {
        ThrowToCS(ret.Msg);
    }
}

void SrvRunnerCLR::SrvRunner::CLear()
{
    STATUS& ret = dllSrvRunner::dllClear();
    if (!ret.Success)
    {
        ThrowToCS(ret.Msg);
    }
}
