// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "../MemoryReplacer/MemoryReplacer.h"
#pragma comment(lib, "..\\x64\\Debug\\MemoryReplacer.lib")

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Injected();
        Replace("Work123123", "Hahaha!");
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

