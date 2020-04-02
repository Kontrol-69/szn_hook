#include "szn.h"

visual_data_t visual_data;
static visuals_t visuals_m;

void visuals_t::get_hitbox_pos(int player)
{
	engine::world_to_screen(&engine::is_valid_tag_pos(player, engine::find_string("j_helmet")), visual_data.top);
	engine::world_to_screen(&entity[player].NextOrigin, visual_data.bottom);

	if (!visual_data.top || !visual_data.bottom)
		return;

	visual_data.pfabs.y = fabsf(visual_data.top.y - visual_data.bottom.y);
	visual_data.pfabs.x = (fabsf(visual_data.top.y - visual_data.bottom.y) * 0.65f);
}

void visuals_t::bounding_box(ImVec4 color)
{
	switch (cvar::player_bounding_box_type)
	{
	case 0:
		break;
	case 1:
		render()->two_d_bounding(visual_data.top.x, visual_data.top.y, visual_data.pfabs.x, visual_data.pfabs.y, color, 1.5f);
		break;
	case 2:
		render()->corner_bounding(visual_data.top.x, visual_data.top.y, visual_data.pfabs.x, visual_data.pfabs.y, color, 1.5f);
		break;
	}
}

void visuals_t::player_info(int player)
{
	std::string name;

	if (cvar::player_distance)
		name = engine::va("[%.1fm] ", math.get_2d_distance(entity[cg->ClientID].CurrentOrigin, entity[player].CurrentOrigin));
	
	name += cg->client[player].Name;

	if (cvar::player_names)
		render()->text(name.c_str(), ((visual_data.top.x - (visual_data.pfabs.x / 2)) + (visual_data.top.x + (visual_data.pfabs.x / 2))) / 2 - (render()->get_text_size(name.c_str()).x / 2), ((visual_data.top.y - (visual_data.pfabs.y / 2)) + (visual_data.top.y + (visual_data.pfabs.y / 2))) / 2 - (render()->get_text_size(name.c_str()).y / 2) - (render()->get_text_size(name.c_str()).y / 1.9f), vec4_color::white, false, vec4_color::null);
}

void visuals_t::create(void)
{
	if (!engine::is_local_player_ingame())
		return;

	if (cvar::player_visuals)
	{
		for (int i = 0; i < 18; i++)
		{
			if (i != cg->ClientID)
			{
				if (engine::world_to_screen(&entity[i].NextOrigin, visual_data.bottom))
				{
					if (!engine::check_player_team(i) && engine::check_player_state(i))
					{
						this->get_hitbox_pos(i);
						this->bounding_box(vec4_color::red);
						this->player_info(i);
					}
				}
			}
		}
	}

	render()->crosshair(1.5f, vec4_color::crosshair);
}

visuals_t* visuals() { return &visuals_m; }