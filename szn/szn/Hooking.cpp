#include "szn.h"

class bots {
public:
	struct gclient_t {
		char pad_0x0000[0x31DC];  // 0
		unsigned char Team;    // 31DC 
		char pad_0x31DD[0x227];   // 31DD
	};         // Size = 0x3404

	struct gentity_t {
		unsigned int clientnumber;  // 0
		unsigned int eType;    // 4
		char pad_0x0[0x150];   // 8
		gclient_t* gclient;    // 158
		char pad_0x15C[0x118];   // 15C
	};         // Size = 0x274

	void Scr_Notify(int entnum, short stringValue, unsigned int paramcount)
	{
		((void(__cdecl*) (int, int, short, unsigned int))0x580180) (entnum, 0, stringValue, paramcount);
	}

	void Scr_AddString(const char* value)
	{
		((void(__cdecl*) (const char*))0x581100) (value);
	}

	std::vector<gentity_t*> SpawnedBots;
	void bots_assignteam() {
		for (auto& bot : SpawnedBots) {
			Scr_AddString("autoassign");
			Scr_AddString("team_marinesopfor");
			Scr_Notify(bot->clientnumber, *(short*)0x1B6AB60, 2);
		}
	}

	void bots_assignclass() {
		for (auto& bot : SpawnedBots) {
			Scr_AddString("class1");
			Scr_AddString("changeclass");
			Scr_Notify(bot->clientnumber, *(short*)0x1B6AB60, 2);
		}
	}

	void addbots() {
		SpawnedBots.clear();
		for (int i = 0; i < 17; i++) {
			gentity_t* bot = ((gentity_t * (__cdecl*) ())0x588280)();
			SpawnedBots.push_back(bot);
		}
		Sleep(200);
		bots_assignteam();
		Sleep(200);
		bots_assignclass();
	}
};
bots bot;

namespace callback
{
	int*(*cg_drawactiveframe)(int a1, float a2, int a3, int a4, int a5, int a6, int a7, int a8);
	void(*scr_updatescreen)(void);
	void(*cg_calcentitylerppos)(int localclientnum, entity_t* centity);
	void(*cl_writepacket)(int localclientnum);
}

int* hooking::cg_drawactiveframe(int a1, float a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	load_structs();

	if (engine::is_local_player_ingame())
		aimbot::calc_angles();

	return callback::cg_drawactiveframe(a1, a2, a3, a4, a5, a6, a7, a8);
}

void hooking::scr_updatescreen(void)
{
	load_structs();
	memory((void*)0x5CABD9).write("\x90\x90");

	if (engine::is_local_player_ingame())
	{
		engine::spoof_ip();
		engine::modify_dvars();

		memory((void*)0x4B9FE7).write(cvar::remove_recoil ? "\x90\x90\x90\x90\x90" : "\xE8\x74\xFF\xFB\xFF");
		memory((void*)(0x4B50B1 + 0x2E)).write("\x75");
	}

	if (GetAsyncKeyState(VK_HOME) & 0x8000)
		bot.addbots();

	callback::scr_updatescreen();
}

void hooking::cg_calcentitylerppos(int localclientnum, entity_t* centity)
{
	callback::cg_calcentitylerppos(localclientnum, centity);

	if (centity->ClientID == cg->ClientID && cvar::anti_aim && cvar::cg_thirdperson)
	{
		if (cvar::current_pitch != 0)
			cg->client[cg->ClientID].viewAngle.x = cvar::stored_angles[ANGLE_PITCH] + clientactive->spawnAngle.x;

		if (cvar::current_yaw != 0)
			centity->Angles.y = cvar::stored_angles[ANGLE_YAW] + clientactive->spawnAngle.y;
	}
}

void hooking::cl_writepacket(int localclientnum)
{
	usercmd_s* cmd = clientactive->get_cmd(clientactive->CurrentCmd);
	usercmd_s* old_cmd = clientactive->get_cmd(clientactive->CurrentCmd - 1);
	usercmd_s* new_cmd = clientactive->get_cmd(clientactive->CurrentCmd + 2);

	*old_cmd = *cmd;
	old_cmd->serverTime--;

	if (cvar::aimbot)
	{
		if (*(short*)0xAB2CC0 || cvar::aimbot_target != -1)
		{
			if (cvar::auto_fire)
			{
				old_cmd->buttons |= 1;
				cmd->buttons &= ~1;
			}
		}

		if (cg->Health > 0)
		{
			anti_aim::pitch(cmd, new_cmd);
			anti_aim::yaw(cmd);

			aimbot::compensate_spread(old_cmd);
		}
	}

	callback::cl_writepacket(localclientnum);
}

void hooking::setup(void)
{
	MH_Initialize();
	hooking::min_hook(reinterpret_cast<void*>(0x4B0BF0), hooking::cg_drawactiveframe, &callback::cg_drawactiveframe);
	hooking::min_hook(reinterpret_cast<void*>(0x4CB280), hooking::scr_updatescreen, &callback::scr_updatescreen);
	hooking::min_hook(reinterpret_cast<void*>(0x4C0A10), hooking::cl_writepacket, &callback::cl_writepacket);
	hooking::min_hook(reinterpret_cast<void*>(0x48E870), hooking::cg_calcentitylerppos, &callback::cg_calcentitylerppos);

	printf("szn_hooks_loaded\n\n");
}

void hooking::remove(void)
{
	MH_RemoveHook(reinterpret_cast<void*>(0x4B0BF0));
	MH_RemoveHook(reinterpret_cast<void*>(0x4CB280));
	MH_RemoveHook(reinterpret_cast<void*>(0x4C0A10));
	MH_RemoveHook(reinterpret_cast<void*>(0x48E870));
	MH_Uninitialize();

	printf("szn_hooks_removed\n");
}

void hooking::thread(HMODULE module)
{
	d3d::create();
	hooking::setup();

	while (true)
	{
		static system_clock::time_point lastUpdate;
		if (GetAsyncKeyState(VK_INSERT) & 0x8000)
		{
			auto now = system_clock::now();

			if (now - lastUpdate > milliseconds(200))
			{
				lastUpdate = now;
				cvar::is_open = !cvar::is_open;

				*(BYTE*)0x6427DBD = cvar::is_open ? 0x0 : 0x1;
			}
		}

		engine::reload_cancel();

		if (GetAsyncKeyState(VK_DELETE) & 0x8000)
			break;
	}

	if (cvar::is_open)
		*(BYTE*)0x6427DBD = 0x1;

	d3d::remove();
	hooking::remove();

	console::deallocate();
	FreeLibraryAndExitThread(module, 0);
}