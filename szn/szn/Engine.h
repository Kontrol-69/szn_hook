namespace engine
{
	// found both of these on some forum
	template<typename Return, typename... params> Return branch(DWORD_PTR address, params... parameters)
	{
		Return(*function)(params...) = (Return(*)(params...))address;
		return function(parameters...);
	}

	template<typename... params> const char* va(const char* text, params... parameters)
	{
		char Buffer[4096] = { NULL };
		sprintf_s(Buffer, text, parameters...);
		return Buffer;
	}
	//

	extern bool is_local_player_ingame();

	extern unsigned int find_string(const char* string_name);

	extern bool get_world_dobj(entity_t* player, int dobj, int hitbox, D3DXVECTOR3* out);
	extern int get_client_dobj(int player);
	extern bool get_tag_pos(entity_t* player, D3DXVECTOR3* pos, int hitbox);
	extern D3DXVECTOR3 is_valid_tag_pos(int player, int hitbox);
	extern void locational_trace(trace_t* trace, D3DXVECTOR3* start, D3DXVECTOR3* end);
	extern bool is_visible(int player, int hitbox);

	extern int get_weapon_def(int weapon_id);
	extern bool bullet_trace(bullet_fire_params* bullet_enter, trace_t* trace, entity_t* entity, int surface);

	extern bool check_player_team(int player);
	extern bool check_player_state(int player);

	extern void* get_scr_placement();
	extern int world_to_screen(D3DXVECTOR3* worldPos, float* outScreenPos);

	extern void vac_bypass(void);
	extern void spoof_ip(void);

	extern void reload_cancel(void);
	extern void reload_cancel_weapon_switch(void);

	extern dvar_t* field_of_view;
	extern dvar_t* cg_thirdperson;
	extern dvar_t* cg_thirdpersonrange;

	extern dvar_t* find_dvar(const char* dvar_name);
	extern void find_dvars(void);
	extern void modify_dvars(void);
}