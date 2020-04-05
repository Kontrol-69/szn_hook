#include "szn.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        console::allocate();

        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hooking::thread, hModule, NULL, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }

    return true;
}