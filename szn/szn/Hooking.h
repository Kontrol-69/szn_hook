namespace callback
{
	extern int*(*cg_drawactiveframe)(int a1, float a2, int a3, int a4, int a5, int a6, int a7, int a8);
	extern void(*scr_updatescreen)(void);
	extern void(*cg_calcentitylerppos)(int localclientnum, entity_t* centity);
	extern void(*cl_writepacket)(int localclientnum);
}

namespace hooking
{
	template <typename tramp>
	static bool min_hook(LPVOID address, LPVOID function, tramp** trampoline)
	{
		if (*(LPVOID*)trampoline != nullptr)
			return true;

		if (LPVOID(address) != 0)
		{
			MH_STATUS hook_status = MH_CreateHook(LPVOID(address), function, reinterpret_cast<LPVOID*>(trampoline));
			if (((hook_status == MH_OK) || (hook_status == MH_ERROR_ALREADY_CREATED)) && (MH_EnableHook(LPVOID(address)) == MH_OK))
				return true;
		}

		return false;
	}

	extern int* cg_drawactiveframe(int a1, float a2, int a3, int a4, int a5, int a6, int a7, int a8);
	extern void scr_updatescreen(void);
	extern void cg_calcentitylerppos(int localclientnum, entity_t* centity);
	extern void cl_writepacket(int localclientnum);

	extern void setup(void);
	extern void remove(void);

	extern void thread(HMODULE module);
}