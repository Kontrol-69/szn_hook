#include "szn.h"

int anti_aim::get_aa_target() // so we can point our riot shield at players, not the best method but w/e
{
	float max_dist = FLT_MAX;
	int aa_target = -1;

	for (int i = 0; i < 18; i++)
	{
		if (i != cg->ClientID)
		{
			if (engine::check_player_state(i) && !engine::check_player_team(i))
			{
				if (math.distance(entity[i].CurrentOrigin, entity[i].CurrentOrigin) < max_dist)
				{
					max_dist = math.distance(entity[i].CurrentOrigin, entity[i].CurrentOrigin);
					aa_target = i;
				}
			}
		}
	}

	return aa_target;
}

void anti_aim::pitch(usercmd_s* cmd, usercmd_s* new_cmd)
{
	if (!cvar::anti_aim)
		return;

	if (!engine::branch<bool>(0x5BCF60, "mantle_enable") && cvar::anti_aim_mantle_check)
		return;

	switch (cvar::current_pitch)
	{
	case 0:
		break;
	case 1:
		cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(-69.999999999f - clientactive->spawnAngle.x);
		cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
		break;
	case 2:
		cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(69.999999999f - clientactive->spawnAngle.x);
		cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
		break;
	case 3:
		cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(-25.999999999f - clientactive->spawnAngle.x);
		cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
		break;
	case 4:
		cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT((!(new_cmd->serverTime % 2) ? 69.999999999f : -69.999999999f) - clientactive->spawnAngle.x);
		cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
		break;
	case 5:
		cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(cvar::custom_pitch - clientactive->spawnAngle.x);
		cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
		break;
	}

	if (*(int*)(0x8A0ED0 + 0x1E8) == 0x218)
	{
		switch (cvar::pitch_on_sprint)
		{
		case 0:
			break;
		case 1:
			cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(-69.999999999f - clientactive->spawnAngle.x);
			cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
			break;
		case 2:
			cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(69.999999999f - clientactive->spawnAngle.x);
			cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
			break;
		case 3:
			cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(-25.999999999f - clientactive->spawnAngle.x);
			cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
			break;
		case 4:
			cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT((!(new_cmd->serverTime % 2) ? 69.999999999f : -69.999999999f) - clientactive->spawnAngle.x);
			cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
			break;
		case 5:
			cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(cvar::custom_pitch - clientactive->spawnAngle.x);
			cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
			break;
		}
	}

	if ((*(BYTE*)(0x8A10B4) & 8))
	{
		switch (cvar::pitch_on_mantle_hint)
		{
		case 0:
			break;
		case 1:
			cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(-69.999999999f - clientactive->spawnAngle.x);
			cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
			break;
		case 2:
			cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(69.999999999f - clientactive->spawnAngle.x);
			cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
			break;
		case 3:
			cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(-25.999999999f - clientactive->spawnAngle.x);
			cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
			break;
		case 4:
			cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT((!(new_cmd->serverTime % 2) ? 69.999999999f : -69.999999999f) - clientactive->spawnAngle.x);
			cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
			break;
		case 5:
			cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(cvar::custom_pitch - clientactive->spawnAngle.x);
			cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
			break;
		}
	}

	if (cvar::aimbot)
	{
		if (cvar::aimbot_target != -1)
		{
			switch (cvar::pitch_on_target)
			{
			case 0:
				break;
			case 1:
				cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(-69.999999999f - clientactive->spawnAngle.x);
				cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
				break;
			case 2:
				cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(69.999999999f - clientactive->spawnAngle.x);
				cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
				break;
			case 3:
				cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(-25.999999999f - clientactive->spawnAngle.x);
				cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
				break;
			case 4:
				cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT((!(new_cmd->serverTime % 2) ? 69.999999999f : -69.999999999f) - clientactive->spawnAngle.x);
				cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
				break;
			case 5:
				cmd->viewAngles[ANGLE_PITCH] = ANGLE2SHORT(cvar::custom_pitch - clientactive->spawnAngle.x);
				cvar::stored_angles[ANGLE_PITCH] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_PITCH]);
				break;
			}
		}
	}
}

void anti_aim::yaw(usercmd_s* cmd)
{
	if (!cvar::anti_aim)
		return;

	if (!engine::branch<bool>(0x5BCF60, "mantle_enable") && cvar::anti_aim_mantle_check)
		return;

	switch (cvar::current_yaw)
	{
	case 0:
		break;
	case 1:
		if (anti_aim::get_aa_target() != -1)
		{
			cvar::anti_aim_target_tag = engine::is_valid_tag_pos(anti_aim::get_aa_target(), engine::find_string("j_head"));
			cvar::anti_aim_target_angle = math.vec_to_angles(cvar::anti_aim_target_tag - refdef->Origin);

			cvar::anti_aim_target_angle -= clientactive->spawnAngle;

			cvar::anti_aim_target_angle.y -= 185.f;

			cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cvar::anti_aim_target_angle.y);
			cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
		}
		else
		{
			cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(185.f);
			cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
		}
		break;
	case 2:
		cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cmd->serverTime * 5 % rand() % 2 ? 10 : 80);
		cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
		break;
	case 3:
		if (cvar::random_spin_angle > 360)
			cvar::random_spin_angle -= 360;

		cvar::random_spin_angle += 39.9999999999f;
		cmd->viewAngles[1] = ANGLE2SHORT(cvar::random_spin_angle);
		cmd->viewAngles[1] = ANGLE2SHORT(cvar::random_spin_angle * 0.9999998f);
		cmd->viewAngles[1] = ANGLE2SHORT(cmd->viewAngles[1] * 1.9999998f + cvar::random_spin_angle);
		cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
		break;
	case 4:
		cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cvar::custom_yaw);
		cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
		break;
	}

	if (*(int*)(0x8A0ED0 + 0x1E8) == 0x218)
	{
		switch (cvar::yaw_on_sprint)
		{
		case 0:
			break;
		case 1:
			if (anti_aim::get_aa_target() != -1)
			{
				cvar::anti_aim_target_tag = engine::is_valid_tag_pos(anti_aim::get_aa_target(), engine::find_string("j_head"));
				cvar::anti_aim_target_angle = math.vec_to_angles(cvar::anti_aim_target_tag - refdef->Origin);

				cvar::anti_aim_target_angle -= clientactive->spawnAngle;

				cvar::anti_aim_target_angle.y -= 185.f;

				cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cvar::anti_aim_target_angle.y);
				cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
			}
			else
			{
				cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(185.f);
				cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
			}
			break;
		case 2:
			cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cmd->serverTime * 5 % rand() % 2 ? 10 : 80);
			cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
			break;
		case 3:
			if (cvar::random_spin_angle > 360)
				cvar::random_spin_angle -= 360;

			cvar::random_spin_angle += 39.9999999999f;
			cmd->viewAngles[1] = ANGLE2SHORT(cvar::random_spin_angle);
			cmd->viewAngles[1] = ANGLE2SHORT(cvar::random_spin_angle * 0.9999998f);
			cmd->viewAngles[1] = ANGLE2SHORT(cmd->viewAngles[1] * 1.9999998f + cvar::random_spin_angle);
			cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
			break;
		case 4:
			cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cvar::custom_yaw);
			cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
			break;
		}
	}

	if ((*(BYTE*)(0x8A10B4) & 8))
	{
		switch (cvar::yaw_on_mantle_hint)
		{
		case 0:
			break;
		case 1:
			if (anti_aim::get_aa_target() != -1)
			{
				cvar::anti_aim_target_tag = engine::is_valid_tag_pos(anti_aim::get_aa_target(), engine::find_string("j_head"));
				cvar::anti_aim_target_angle = math.vec_to_angles(cvar::anti_aim_target_tag - refdef->Origin);

				cvar::anti_aim_target_angle -= clientactive->spawnAngle;

				cvar::anti_aim_target_angle.y -= 185.f;

				cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cvar::anti_aim_target_angle.y);
				cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
			}
			else
			{
				cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(185.f);
				cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
			}
			break;
		case 2:
			cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cmd->serverTime * 5 % rand() % 2 ? 10 : 80);
			cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
			break;
		case 3:
			if (cvar::random_spin_angle > 360)
				cvar::random_spin_angle -= 360;

			cvar::random_spin_angle += 39.9999999999f;
			cmd->viewAngles[1] = ANGLE2SHORT(cvar::random_spin_angle);
			cmd->viewAngles[1] = ANGLE2SHORT(cvar::random_spin_angle * 0.9999998f);
			cmd->viewAngles[1] = ANGLE2SHORT(cmd->viewAngles[1] * 1.9999998f + cvar::random_spin_angle);
			cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
			break;
		case 4:
			cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cvar::custom_yaw);
			cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
			break;
		}
	}

	if (cvar::aimbot)
	{
		if (cvar::aimbot_target != -1)
		{
			switch (cvar::yaw_on_target)
			{
			case 0:
				break;
			case 1:
				if (anti_aim::get_aa_target() != -1)
				{
					cvar::anti_aim_target_tag = engine::is_valid_tag_pos(anti_aim::get_aa_target(), engine::find_string("j_head"));
					cvar::anti_aim_target_angle = math.vec_to_angles(cvar::anti_aim_target_tag - refdef->Origin);

					cvar::anti_aim_target_angle -= clientactive->spawnAngle;

					cvar::anti_aim_target_angle.y -= 185.f;

					cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cvar::anti_aim_target_angle.y);
					cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
				}
				else
				{
					cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(185.f);
					cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
				}
				break;
			case 2:
				cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cmd->serverTime * 5 % rand() % 2 ? 10 : 80);
				cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
				break;
			case 3:
				if (cvar::random_spin_angle > 360)
					cvar::random_spin_angle -= 360;

				cvar::random_spin_angle += 39.9999999999f;
				cmd->viewAngles[1] = ANGLE2SHORT(cvar::random_spin_angle);
				cmd->viewAngles[1] = ANGLE2SHORT(cvar::random_spin_angle * 0.9999998f);
				cmd->viewAngles[1] = ANGLE2SHORT(cmd->viewAngles[1] * 1.9999998f + cvar::random_spin_angle);
				cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
				break;
			case 4:
				cmd->viewAngles[ANGLE_YAW] = ANGLE2SHORT(cvar::custom_yaw);
				cvar::stored_angles[ANGLE_YAW] = (float)SHORT2ANGLE(cmd->viewAngles[ANGLE_YAW]);
				break;
			}
		}
	}
}