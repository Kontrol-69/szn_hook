#include "szn.h"

void console::allocate(void)
{
#ifdef _DEBUG
	FILE* f;
	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	SetConsoleTitle(L"szn_iw4mp_debug");
	system("color 5");
	freopen_s(&f, "CONOUT$", "w", stdout);

	printf("szn_console_created\n");
#endif
}

void console::deallocate(void)
{
	printf("szn_console_removed\n");
	FreeConsole();
}