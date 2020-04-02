namespace vec4_color
{
	extern ImVec4 null;

	extern ImVec4 white;
	extern ImVec4 black;
	extern ImVec4 red;
	extern ImVec4 green;
	extern ImVec4 blue;

	extern ImVec4 crosshair;
}

class rendering_t
{
private:
	RECT rect;
public:
	int get_window_width(void);
	int get_window_height(void);

	ImVec2 get_text_size(const char* text, ...);
	ImU32 get_u32_color(ImVec4 color);

	void text(const char* text, float x, float y, ImVec4 color, bool is_outlined, ImVec4 outlined_color);
	void line(float x, float y, float x2, float y2, ImVec4 color, float thickness);

	void corner_bounding(float x, float y, float w, float h, ImVec4 color, float thickness);
	void two_d_bounding(float x, float y, float w, float h, ImVec4 color, float thickness);
	void crosshair(float size, ImVec4 color);

	void begin_imgui_frame(void);
	void end_imgui_frame(void);

	void begin_menu_imgui_instance(void);

	void create_menu_imgui_aimbot_options(void);
	void create_menu_imgui_visual_options(void);
	void create_menu_imgui_misc_options(void);
	void create_menu_imgui_options(void);

	void end_menu_imgui_instance(void);

	void begin_esp_imgui_instance(void);
	void end_esp_imgui_instance(void);
};

extern rendering_t* render();