struct visual_data_t
{
	D3DXVECTOR3 top, bottom;
	D3DXVECTOR2 pfabs;
	D3DXVECTOR2 screen;
}; extern visual_data_t visual_data;

class visuals_t
{
public:
	void get_hitbox_pos(int player);

	void bounding_box(ImVec4 color);
	void player_info(int player);

	void create(void);
};

extern visuals_t* visuals();