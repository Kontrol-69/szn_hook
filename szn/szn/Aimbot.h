struct allocate_bone_t
{
	unsigned int
		J_HELMET =			engine::find_string("j_helmet"),
		J_HEAD =			engine::find_string("j_head"),
		J_JAW =				engine::find_string("j_jaw"),
		J_NECK =			engine::find_string("j_neck"),
		TAG_EYE =			engine::find_string("tag_eye"),
		J_SHOULDER_LE =		engine::find_string("j_shoulder_le"),
		J_SHOULDER_RI =		engine::find_string("j_shoulder_ri"),
		J_SPINE4 =			engine::find_string("j_spine4"),
		J_SPINEUPPER =		engine::find_string("j_spineupper"),
		J_SPINELOWER =		engine::find_string("j_spinelower"),
		J_ELBOW_LE =		engine::find_string("j_elbow_le"),
		J_ELBOW_RI =		engine::find_string("j_elbow_ri"),
		J_HIP_LE =			engine::find_string("j_hip_le"),
		J_HIP_RI =			engine::find_string("j_hip_ri"),
		J_KNEE_LE =			engine::find_string("j_knee_le"),
		J_KNEE_RI =			engine::find_string("j_knee_ri"),
		J_ANKLE_LE =		engine::find_string("j_ankle_le"),
		J_ANKLE_RI =		engine::find_string("j_ankle_ri"),
		J_BALL_LE =			engine::find_string("j_ball_le"),
		J_BALL_RI =			engine::find_string("j_ball_ri");
};

struct target_info_t
{
	float distance;
	int target;
	D3DXVECTOR3 hitbox;
};

struct nospread_t
{
	complete_weapon_def_t* weapon;
	float spread, min_spread, max_spread;

	unsigned int transform_seed;
	float transformed_spread[2];
	float spread_x, spread_y;
};

namespace aimbot
{
	extern unsigned int allocate_bonescan[];

	extern bool bonescan_hitboxes(int player, D3DXVECTOR3* pos);
	extern int get_best_target(void);
	extern void calc_angles(void);

	extern float autowall(D3DXVECTOR3 start, D3DXVECTOR3 end);

	extern void first_bullet_fix(void);
	extern void bg_get_spread_for_weapon(complete_weapon_def_t* weapon, float* min_spread, float* max_spread);
	extern void get_spread(float* spread);
	extern unsigned int transform_seed(unsigned int seed);
	extern void compensate_spread(usercmd_s* cmd);
}

extern allocate_bone_t allocate_bone;
extern target_info_t target_info;
extern nospread_t nospread;