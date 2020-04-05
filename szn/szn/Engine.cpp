#include "szn.h"

bool Dvar_GetBool(const char* cmd)
{
	return ((bool(*)(...))0x5BCF60)(cmd);
}

bool engine::is_local_player_ingame()
{
	if (Dvar_GetBool("cl_ingame"))
		return true;

	return false;
}

unsigned int engine::find_string(const char* string_name)
{
	return engine::branch<int>(0x579EF0, string_name);
}

bool engine::get_world_dobj(entity_t* player, int dobj, int hitbox, D3DXVECTOR3* out)
{
	return engine::branch<bool>(0x48E720, player, dobj, hitbox, out);
}

int engine::get_client_dobj(int player)
{
	return engine::branch<int>(0x56B8E0, player, 0);
}

bool engine::get_tag_pos(entity_t* player, D3DXVECTOR3* pos, int hitbox)
{
	if (engine::get_client_dobj(player->ClientID))
		engine::get_world_dobj(player, engine::get_client_dobj(player->ClientID), hitbox, pos);

	return pos;
}

D3DXVECTOR3 engine::is_valid_tag_pos(int player, int hitbox)
{
	D3DXVECTOR3 pos;

	if (engine::get_tag_pos(&entity[player], &pos, hitbox))
		return pos;

	return D3DXVECTOR3();
}

void engine::locational_trace(trace_t* trace, D3DXVECTOR3* start, D3DXVECTOR3* end)
{
	engine::branch<void>(0x4BB120, trace, start, end, cg->ClientID, 0x803003);
}

bool engine::is_visible(int player, int hitbox)
{
	engine::locational_trace(&trace, &refdef->Origin, &engine::is_valid_tag_pos(player, hitbox));
	return trace.fraction >= 1.f;
}

int engine::get_weapon_def(int weapon_id)
{
	return engine::branch<int>(0x479510, weapon_id);
}

bool engine::bullet_trace(bullet_fire_params* bullet_enter, trace_t* trace, entity_t* entity, int surface)
{
	bool uk;
	DWORD fcall = 0x4B4520;

	__asm
	{
		push[surface]
		push[entity]
		mov esi, [trace]
		mov eax, [bullet_enter]
		call[fcall]
		add esp, 0x8
		mov[uk], al
	}

	return uk;
}

bool engine::check_player_team(int player)
{
	return cg->client[player].Team == cg->client[cg->ClientID].Team && strcmp(reinterpret_cast<char*>(0x89D440), "dm");
}

bool engine::check_player_state(int player)
{
	if (player == cg->ClientID || !(entity[player].isAlive & 1) || engine::check_player_team(player))
		return false;

	return true;
}

void* engine::get_scr_placement()
{
	return engine::branch<void*>(0x4DF860, NULL);
}

int engine::world_to_screen(D3DXVECTOR3* worldPos, float* outScreenPos)
{
	return engine::branch<int>(0x48BF30, NULL, engine::get_scr_placement(), worldPos, outScreenPos);
}

void engine::vac_bypass(void)
{
	if (!*reinterpret_cast<BYTE*>(0x66547A9) && !*reinterpret_cast<BYTE*>(0x66547AB))
	{
		*reinterpret_cast<BYTE*>(0x66547A9) = 1;
		engine::branch<int>(0x627B90, *reinterpret_cast<int*>(0x66547BC));
	}
}

void engine::spoof_ip(void)
{
	if (cvar::spoof_ip)
	{
		*reinterpret_cast<BYTE*>(0x6466898) = 69;
		*reinterpret_cast<BYTE*>(0x6466899) = 69;
		*reinterpret_cast<BYTE*>(0x646689A) = 69;
		*reinterpret_cast<BYTE*>(0x646689B) = 69;
	}
}

void engine::reload_cancel(void)
{
	if (cg == nullptr)
		return;

	if (cvar::reload_cancel)
	{
		bool IsReloading;

		IsReloading = *reinterpret_cast<int*>(0x8A10C8) == 0x8;

		if (IsReloading && *reinterpret_cast<int*>(0x8A0ED0 + 0x1F0) == 0)
			engine::reload_cancel_weapon_switch();
	}
}

void engine::reload_cancel_weapon_switch(void)
{
	keybd_event(static_cast<BYTE>(VkKeyScan('1')), 0x10, 0, 0);
	Sleep(1);
	keybd_event(static_cast<BYTE>(VkKeyScan('1')), 0x10, KEYEVENTF_KEYUP, 0);
	Sleep(1);
	keybd_event(static_cast<BYTE>(VkKeyScan('1')), 0x10, 0, 0);
	Sleep(1);
	keybd_event(static_cast<BYTE>(VkKeyScan('1')), 0x10, KEYEVENTF_KEYUP, 0);
}

dvar_t* engine::find_dvar(const char* dvar_name)
{
	// -- ty for the help with this salty/clint
	for (int i = 0; i < *reinterpret_cast<int*>(0x637C448); i++)
	{
		dvar_t* dvar = reinterpret_cast<dvar_t*>(0x6381470 + 76 * i);

		if (dvar && !strcmp(dvar->name, dvar_name))
			return dvar;
	}

	return NULL;
}

dvar_t* engine::field_of_view;
dvar_t* engine::cg_thirdperson;
dvar_t* engine::cg_thirdpersonrange;
void engine::find_dvars(void)
{
	engine::field_of_view = engine::find_dvar("cg_fov");
	engine::cg_thirdperson = engine::find_dvar("cg_thirdPerson");
	engine::cg_thirdpersonrange = engine::find_dvar("cg_thirdPersonRange");
}

void engine::modify_dvars(void)
{
	engine::find_dvars();

	engine::field_of_view->setFloat(cvar::cg_thirdperson ? 65.f : cvar::field_of_view);
	engine::cg_thirdperson->setInt(cvar::cg_thirdperson);
	engine::cg_thirdpersonrange->setFloat(cvar::thirdperson_range);
}