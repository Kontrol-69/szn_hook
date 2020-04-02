#include "szn.h"

namespace cvar
{
	bool is_open;

	bool aimbot, aimbot_autowall, compensate_spread, auto_fire;
	int aimbot_target, surface_count = 5, bonescan_amount = 1;
	D3DXVECTOR3 aimbot_angle, thirdperson_aimbot_angle;

	bool anti_aim, anti_aim_mantle_check;
	float stored_angles[3];
	int current_pitch, pitch_on_sprint, pitch_on_mantle_hint, pitch_on_target;
	int current_yaw, yaw_on_sprint, yaw_on_mantle_hint, yaw_on_target;
	float random_spin_angle, custom_pitch, custom_yaw;
	D3DXVECTOR3 anti_aim_target_tag, anti_aim_target_angle;

	bool player_visuals, player_names, player_distance;
	int player_bounding_box_type;

	bool crosshair, cg_thirdperson, remove_recoil;
	float field_of_view = 65.f, thirdperson_range = 150.f;

	bool spoof_ip, reload_cancel;
}