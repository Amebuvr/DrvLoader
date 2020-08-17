#pragma once

extern "C" __declspec(dllexport) void Create(WCHAR*, WCHAR*);
extern "C" __declspec(dllexport) void Start();
extern "C" __declspec(dllexport) void Stop();
extern "C" __declspec(dllexport) void Delete();

SC_HANDLE hSCManager, hService;