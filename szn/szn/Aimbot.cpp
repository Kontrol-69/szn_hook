#include "szn.h"

allocate_bone_t allocate_bone;
target_info_t target_info;
nospread_t nospread;

unsigned int aimbot::allocate_bonescan[] =
{
	allocate_bone.J_HEAD,
	allocate_bone.J_NECK,

	allocate_bone.J_SHOULDER_RI,
	allocate_bone.J_SHOULDER_LE,

	allocate_bone.J_SPINE4,
	allocate_bone.J_SPINEUPPER,
	allocate_bone.J_SPINELOWER,

	allocate_bone.J_ELBOW_RI,
	allocate_bone.J_ELBOW_LE,

	allocate_bone.J_HIP_RI,
	allocate_bone.J_HIP_LE,

	allocate_bone.J_KNEE_RI,
	allocate_bone.J_KNEE_LE,

	allocate_bone.J_ANKLE_RI,
	allocate_bone.J_ANKLE_LE,

	allocate_bone.J_BALL_RI,
	allocate_bone.J_BALL_LE
};

bool aimbot::bonescan_hitboxes(int player, D3DXVECTOR3* pos)
{
	D3DXVECTOR3 end;
	engine::branch<void>(0x4B4480, NULL, cg, &cvar::aimbot_angle);

	for (int i = 0; i < cvar::bonescan_amount; i++)
	{
		end = engine::is_valid_tag_pos(player, aimbot::allocate_bonescan[i]);

		if (cvar::aimbot_autowall ? aimbot::autowall(cvar::aimbot_angle, end) : engine::is_visible(player, aimbot::allocate_bonescan[i]))
		{
			*pos = end;
			return true;
		}
	}

	return false;
}

float aimbot::autowall(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	if (cg->Health <= 0)
		return -1.f;

	int local_index;
	entity_t* local_entity;
	complete_weapon_def_t* weapon;

	local_index = cg->ClientID;
	local_entity = &entity[local_index];
	weapon = reinterpret_cast<complete_weapon_def_t*>(engine::get_weapon_def(local_entity->WeaponID));

	if (!weapon)
		return -1.f;

	bullet_fire_params bullet_enter, bullet_exit;
	trace_t trace_enter, trace_exit;

	D3DXVECTOR3 full_rotation, copy_trace_hit;

	bool is_traced_hit, fmj_perk = cg->client[local_index].Perk & 0x20, exit_trace, solid_trace;
	int traced_surface_count = 0;
	float weapon_depth, bullet_enter_depth, bullet_exit_depth, trace_surface_depth;

	bullet_enter.WorldEntNum = 0x3FE;
	bullet_enter.ignoreEntIndex = local_index;
	bullet_enter.damageMultiplier = 2.f;
	bullet_enter.methodOfDeath = (*(BYTE*)(weapon + 0x65C) != 0) + 1;

	VectorCopy(start, bullet_enter.Origin);
	VectorCopy(start, bullet_enter.Start);
	VectorCopy(end, bullet_enter.End);

	VectorSubtract(end, start, full_rotation);
	math.normalize_vector(full_rotation);
	VectorCopy(full_rotation, (D3DXVECTOR3&)bullet_enter.Dir);

	is_traced_hit = engine::bullet_trace(&bullet_enter, &trace_enter, local_entity, 0);

	if (is_traced_hit)
	{
		while (true)
		{
			bullet_enter_depth = engine::branch<float>(0x479430, weapon, trace_enter.materialType);

			if (trace_enter.surfaceFlags & 4)
				bullet_enter_depth = 100.f;

			bullet_enter_depth *= fmj_perk ? 2.f : 1.f;

			if (bullet_enter_depth < 0.f)
				return 0.f;

			weapon_depth = *(float*)(weapon + 0x30) * (bullet_enter_depth * 0.50251256281f);

			if (*(DWORD*)(weapon + 0xE0) == 1 && fmj_perk)
				weapon_depth *= *(float*)(*(DWORD*)0x86CC24 + 0xC);

			if (weapon_depth <= 0.f)
				return 0.f;

			VectorCopy(trace_enter.endpos, copy_trace_hit);

			if (!engine::branch<bool>(0x479A80, &bullet_enter, &trace_enter, 0.13500001f))
				return 0.f;

			is_traced_hit = engine::bullet_trace(&bullet_enter, &trace_enter, local_entity, trace_enter.materialType);

			CopyMemory(&bullet_exit, &bullet_enter, sizeof(bullet_fire_params));
			VectorScale(bullet_enter.Dir, -2.f, bullet_exit.Dir);

			VectorCopy(bullet_enter.End, bullet_exit.Start);
			VectorMA(copy_trace_hit, 0.009999999776482582f, bullet_exit.Dir, bullet_exit.End);

			CopyMemory(&trace_exit, &trace_enter, sizeof(trace_t));
			VectorScale(trace_exit.surfaceDirection, -2.f, trace_exit.surfaceDirection);

			if (is_traced_hit)
				engine::branch<bool>(0x479A80, &bullet_exit, &trace_exit, 0.0099999998f);

			exit_trace = engine::bullet_trace(&bullet_exit, &trace_exit, local_entity, trace_exit.materialType);
			solid_trace = exit_trace && trace_exit.allsolid || trace_enter.startsolid && trace_exit.startsolid;

			if (trace_exit.materialType == 0 && trace_enter.materialType == 0)
				return bullet_enter.damageMultiplier;

			if (exit_trace || solid_trace)
			{
				if (solid_trace)
					trace_surface_depth = engine::branch<float>(0x412A20, &bullet_exit.End, &bullet_exit.Start);
				else
					trace_surface_depth = engine::branch<float>(0x412A20, &copy_trace_hit, &trace_exit.endpos);

				trace_surface_depth = max(trace_surface_depth, 2.f);

				if (exit_trace)
				{
					bullet_exit_depth = engine::branch<float>(0x479430, weapon, trace_exit.materialType);

					if (trace_exit.surfaceFlags & 4)
						bullet_exit_depth = 100.f;

					bullet_exit_depth *= fmj_perk ? 2.f : 1.f;

					bullet_enter_depth = min(bullet_enter_depth, bullet_exit_depth);

					if (bullet_enter_depth <= 0.f)
						return 0.f;

					weapon_depth = *(float*)(weapon + 0x30) * (bullet_enter_depth * 0.50251256281f);

					if (*(DWORD*)(weapon + 0xE0) == 1 && fmj_perk)
						weapon_depth *= *(float*)(*(DWORD*)0x86CC24 + 0xC);

					if (weapon_depth < 0.f)
						return 0.f;
				}

				bullet_enter.damageMultiplier -= trace_surface_depth / bullet_enter_depth;

				if (bullet_enter.damageMultiplier <= 0.f)
					return 0.f;
			}
			else if (!is_traced_hit)
				return bullet_enter.damageMultiplier;

			if (is_traced_hit)
				if (++traced_surface_count < cvar::surface_count)
					continue;

			return 0.f;
		}
	}

	return bullet_enter.damageMultiplier;
}

int aimbot::get_best_target(void)
{
	target_info.distance = FLT_MAX;
	target_info.target = -1;

	for (int i = 0; i < 18; i++)
	{
		if (i != cg->ClientID)
		{
			if (!engine::check_player_team(i) && engine::check_player_state(i))
			{
				if (aimbot::bonescan_hitboxes(i, &target_info.hitbox))
				{
					if (math.get_2d_distance(entity[cg->ClientID].CurrentOrigin, entity[i].CurrentOrigin) < target_info.distance)
					{
						target_info.distance = math.distance(entity[cg->ClientID].CurrentOrigin, entity[i].CurrentOrigin);
						target_info.target = i;
					}
				}
			}
		}
	}

	return target_info.target;
}

void aimbot::calc_angles(void)
{
	if (!cvar::aimbot)
		return;

	cvar::aimbot_target = aimbot::get_best_target();

	if (cvar::aimbot_target != -1)
	{
		cvar::aimbot_angle = math.vec_to_angles(target_info.hitbox - cvar::aimbot_angle) - clientactive->spawnAngle;
		clientactive->viewAngle = cvar::aimbot_angle;
	}
}

void aimbot::first_bullet_fix(void)
{
	// cg_drawactive
	float v2, v3, v4, v5;

	v2 = *reinterpret_cast<float*>(0x91362C);

	if (*reinterpret_cast<float*>(0x914E3C) != 0.f)
		v2 = *reinterpret_cast<float*>(0x914E3C) * *reinterpret_cast<float*>(0x91362C);

	engine::branch<void>(0x4BBE50, NULL, v2);

	v3 = *reinterpret_cast<float*>(0x914DA0) + *reinterpret_cast<float*>(0x914D94);
	v4 = *reinterpret_cast<float*>(0x914DA4) + *reinterpret_cast<float*>(0x914D98);
	v5 = *reinterpret_cast<float*>(0x914DA8) + *reinterpret_cast<float*>(0x914D9C);

	engine::branch<void>(0x4BBDB0, NULL, &v3);
	engine::branch<void>(0x4BBD90, NULL, *reinterpret_cast<int*>(0x913F1C), *reinterpret_cast<int*>(0x914A24));
	engine::branch<void>(0x4BBE60, NULL, *reinterpret_cast<int*>(0x99E1C4));
	*reinterpret_cast<int*>(0x99E1C4) = 0;
}

void aimbot::bg_get_spread_for_weapon(complete_weapon_def_t* weapon, float* min_spread, float* max_spread)
{
	int* cg;
	float viewHeightCurrent, f_spread_calc, f_spread_calc_a, *end_spread;

	cg = (int*)0x8A0ED0;

	if (*((int*)cg + 0xB4) == 2)
	{
		*min_spread = (float)*((int*)cg + 0xB3);
		*max_spread = (float)*((int*)cg + 0xB3);
	}
	else
	{
		viewHeightCurrent = *((float*)cg + 0x47);

		if (viewHeightCurrent <= 40.f)
		{
			f_spread_calc = (float)(viewHeightCurrent - 11.f) * 0.034482758f;

			*min_spread = (*((float*)weapon + 0xCF) - *((float*)weapon + 0xD0)) * f_spread_calc + *((float*)weapon + 0xD0);
			*max_spread = f_spread_calc * (*((float*)weapon + 0xD2) - *((float*)weapon + 0xD3)) + *((float*)weapon + 0xD3);
		}
		else
		{
			f_spread_calc_a = (viewHeightCurrent - 40.f) * 0.05f;

			*min_spread = (*((float*)weapon + 0xCE) - *((float*)weapon + 0xCF)) * f_spread_calc_a + *((float*)weapon + 0xCF);
			*max_spread = f_spread_calc_a * (*((float*)weapon + 0xD1) - *((float*)weapon + 0xD2)) + *((float*)weapon + 0xD2);
		}
	}

	if (*((int*)cg + 0xB4) == 1)
		*max_spread = (float)*((int*)cg + 0xB3);

	if (*((BYTE*)cg + 0x428) & 2)
	{
		end_spread = (float*)(*(int*)0x86CC2C + 0xC);
		*min_spread = *min_spread * *(float*)(*(int*)0x86CC2C + 0xC);
		*max_spread = *max_spread * *end_spread;
	}
}

void aimbot::get_spread(float* spread)
{
	nospread.weapon = reinterpret_cast<complete_weapon_def_t*>(engine::get_weapon_def(entity[cg->ClientID].WeaponID));

	if (!nospread.weapon)
		return;

	aimbot::bg_get_spread_for_weapon(nospread.weapon, &nospread.min_spread, &nospread.max_spread);
	*spread = nospread.min_spread + ((nospread.max_spread - nospread.min_spread) * (cg->hipfireSpread * 0.00392157f));
}

unsigned int aimbot::transform_seed(unsigned int seed)
{
	return 0x343FD * (0x343FD * (0x343FD * (0x343FD * (0x343FD * seed + 0x269EC3) + 0x269EC3) + 0x269EC3) + 0x269EC3) + 0x269EC3;
}

void aimbot::compensate_spread(usercmd_s* cmd)
{
	if (!cvar::compensate_spread)
		return;

	if (cg->client[cg->ClientID].isAds)
		return;

	aimbot::first_bullet_fix();
	aimbot::get_spread(&nospread.spread);

	nospread.transform_seed = aimbot::transform_seed(cmd->serverTime);

	nospread.transformed_spread[0] = (nospread.transform_seed >> 17) * 0.000030517578125f * 360.0f * 0.01745329238474369f;
	nospread.transformed_spread[1] = (static_cast<unsigned int>(0x343FD * nospread.transform_seed + 0x269EC3) >> 17) * 0.000030517578125f;

	nospread.spread_x = sin(nospread.transformed_spread[0]) * nospread.transformed_spread[1] * -nospread.spread;
	nospread.spread_y = cos(nospread.transformed_spread[0]) * nospread.transformed_spread[1] * -nospread.spread;

	cmd->viewAngles[0] -= ANGLE2SHORT(nospread.spread_x);
	cmd->viewAngles[1] -= ANGLE2SHORT(nospread.spread_y);
}