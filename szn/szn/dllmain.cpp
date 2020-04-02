#include "szn.h"

/*
if (gCvars.hvh_aay == 9)
{
	angles.y -= 90;

	if (angles.y >= 90)
		angles.y += pCommand->tick_count * 5 % 180;
	else
		angles.y -= pCommand->tick_count * 5 % 180;
}
*/

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