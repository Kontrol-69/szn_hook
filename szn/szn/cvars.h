namespace cvar
{
	extern bool is_open;

	extern bool aimbot, aimbot_autowall, compensate_spread, auto_fire;
	extern int aimbot_target, surface_count, bonescan_amount;
	extern D3DXVECTOR3 aimbot_angle, thirdperson_aimbot_angle;

	extern bool anti_aim, anti_aim_mantle_check;
	extern float stored_angles[3];
	extern int current_pitch, pitch_on_sprint, pitch_on_mantle_hint, pitch_on_target;
	extern int current_yaw, yaw_on_sprint, yaw_on_mantle_hint, yaw_on_target;
	extern float random_spin_angle, custom_pitch, custom_yaw;
	extern D3DXVECTOR3 anti_aim_target_tag, anti_aim_target_angle;

	extern bool player_visuals, player_names, player_distance;
	extern int player_bounding_box_type;

	extern bool crosshair, cg_thirdperson, remove_recoil;
	extern float field_of_view, thirdperson_range;

	extern bool spoof_ip, reload_cancel;
}