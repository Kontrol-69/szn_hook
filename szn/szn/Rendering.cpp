#include "szn.h"

static rendering_t rendering_m;

namespace vec4_color
{
	ImVec4 null = { 0, 0, 0, 0 };

	ImVec4 white = { 1, 1, 1, 1 };
	ImVec4 black = { 0, 0, 0, 1 };
	ImVec4 red = { 1, 0, 0, 1 };
	ImVec4 green = { 0, 1, 0, 1 };
	ImVec4 blue = { 0, 0, 1, 1 };

	ImVec4 crosshair = { 1, 1, 1, 1 };
}

int rendering_t::get_window_width(void)
{
	GetWindowRect(FindWindow(NULL, L"Modern Warfare 2"), &this->rect);
	return this->rect.right - this->rect.left;
}

int rendering_t::get_window_height(void)
{
	GetWindowRect(FindWindow(NULL, L"Modern Warfare 2"), &this->rect);
	return this->rect.bottom - this->rect.top;
}

ImVec2 rendering_t::get_text_size(const char* text, ...)
{
	char buffer[0x1000];
	ZeroMemory(buffer, sizeof(buffer));

	va_list list;
	va_start(list, text);
	vsnprintf(buffer, sizeof(buffer), text, list);
	va_end(list);

	return ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, 0.f, buffer);
}

ImU32 rendering_t::get_u32_color(ImVec4 color)
{
	return ImGui::GetColorU32(color);
}

void rendering_t::text(const char* text, float x, float y, ImVec4 color, bool is_outlined, ImVec4 outlined_color)
{
	if (is_outlined)
	{
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1.5f, y - 1.5f), this->get_u32_color(outlined_color), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y - 1.5f), this->get_u32_color(outlined_color), text);

		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1.5f, y - 1.5f), this->get_u32_color(outlined_color), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1.5f, y), this->get_u32_color(outlined_color), text);

		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1.5f, y + 1.5f), this->get_u32_color(outlined_color), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1.5f), this->get_u32_color(outlined_color), text);

		ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1.5f, y + 1.5f), this->get_u32_color(outlined_color), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1.5f, y), this->get_u32_color(outlined_color), text);
	}

	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), this->get_u32_color(color), text);
}

void rendering_t::line(float x, float y, float x2, float y2, ImVec4 color, float thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y), ImVec2(x2, y2), ImGui::GetColorU32(color), thickness);
}

void rendering_t::corner_bounding(float x, float y, float w, float h, ImVec4 color, float thickness)
{
	this->line(x + (w / 2), y + h, x + (w / 2) - (w / 3), y + h, color, thickness);
	this->line(x - (w / 2), y + h, x - (w / 2) + (w / 3), y + h, color, thickness);

	this->line(x - (w / 2), y, x - (w / 2) + (w / 3), y, color, thickness);
	this->line(x + (w / 2), y, x + (w / 2) - (w / 3), y, color, thickness);

	this->line(x - (w / 2), y, x - (w / 2), y + (w / 3), color, thickness);
	this->line(x + (w / 2), y, x + (w / 2), y + (w / 3), color, thickness);

	this->line(x - (w / 2), y + h, x - (w / 2), y + h - (w / 3), color, thickness);
	this->line(x + (w / 2), y + h, x + (w / 2), y + h - (w / 3), color, thickness);
}

void rendering_t::two_d_bounding(float x, float y, float w, float h, ImVec4 color, float thickness)
{
	this->line(x + (w / 2), y + h, x + (w / 2) - (w / 1), y + h, color, thickness);
	this->line(x - (w / 2), y + h, x - (w / 2) + (w / 1), y + h, color, thickness);

	this->line(x - (w / 2), y, x - (w / 2) + (w / 1), y, color, thickness);
	this->line(x + (w / 2), y, x + (w / 2) - (w / 1), y, color, thickness);

	this->line(x - (w / 2), y, x - (w / 2), y + (w / 1), color, thickness);
	this->line(x + (w / 2), y, x + (w / 2), y + (w / 1), color, thickness);

	this->line(x - (w / 2), y + h, x - (w / 2), y + h - (w / 1), color, thickness);
	this->line(x + (w / 2), y + h, x + (w / 2), y + h - (w / 1), color, thickness);
}

void rendering_t::crosshair(float size, ImVec4 color)
{
	float width, height = 0;

	width = (float)uicontext.screenWidth / 2;
	height = (float)uicontext.screenHeight / 2;

	if (cvar::crosshair)
	{
		this->line(width, height - 9, width, height - 2, color, size);
		this->line(width - 9, height, width - 2, height, color, size);
		this->line(width + 9, height, width + 2, height, color, size);
		this->line(width, height + 9, width, height + 2, color, size);
	}
}

void rendering_t::begin_imgui_frame(void)
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void rendering_t::end_imgui_frame(void)
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void rendering_t::begin_menu_imgui_instance(void)
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImGuiIO& io = ImGui::GetIO();

	style.WindowPadding = ImVec2(5, 5);
	style.WindowRounding = 5.f;
	style.FramePadding = ImVec2(2, 2);
	style.FrameRounding = 5.f;
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(4, 3);
	style.IndentSpacing = 25.f;
	style.ItemSpacing = ImVec2(5, 5);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.GrabRounding = 5.f;

	io.WantCaptureKeyboard = true;
	io.WantCaptureMouse = true;

	if (cvar::is_open)
		ImGui::Begin("szn_hook", NULL, ImVec2(375, 375), 1.f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
}

void rendering_t::create_menu_imgui_aimbot_options(void)
{
	if (ImGui::CollapsingHeader("szn_ragebot"))
	{
		ImGui::Checkbox("active##15189", &cvar::aimbot);
		ImGui::Separator();

		ImGui::Checkbox("penetration check", &cvar::aimbot_autowall);

		ImGui::PushItemWidth(125);
		ImGui::SliderInt("surface count", &cvar::surface_count, 5, 12);
		ImGui::PopItemWidth();

		ImGui::Checkbox("compensate spread", &cvar::compensate_spread);
		ImGui::Checkbox("auto-fire", &cvar::auto_fire);

		ImGui::Text("bonescan amount", cvar::bonescan_amount);
		ImGui::PushItemWidth(125);
		ImGui::SliderInt("##15787", &cvar::bonescan_amount, 1, 17);
		ImGui::PopItemWidth();
	}

	if (ImGui::CollapsingHeader("szn_anti_aim"))
	{
		ImGui::Checkbox("active##0", &cvar::anti_aim);
		ImGui::Separator();

		ImGui::Text("pitch");
		ImGui::SameLine(135);
		ImGui::Text("yaw");
		ImGui::Separator();

		ImGui::PushItemWidth(125);
		ImGui::Combo("##0", &cvar::current_pitch, "disabled\0up\0down\0semi-up\0jitter\0custom");
		ImGui::SameLine();
		ImGui::Combo("default", &cvar::current_yaw, "disabled\0backwards\0jitter\0spin\0custom");

		ImGui::Combo("##1", &cvar::pitch_on_sprint, "disabled\0up\0down\0semi-up\0jitter\0custom");
		ImGui::SameLine();
		ImGui::Combo("on-sprint", &cvar::yaw_on_sprint, "disabled\0backwards\0jitter\0spin\0custom");

		ImGui::Combo("##18741", &cvar::pitch_on_target, "disabled\0up\0down\0semi-up\0jitter\0custom");
		ImGui::SameLine();
		ImGui::Combo("on-target", &cvar::yaw_on_target, "disabled\0backwards\0jitter\0spin\0custom");

		ImGui::Combo("##3", &cvar::pitch_on_mantle_hint, "disabled\0up\0down\0semi-up\0jitter\0custom");
		ImGui::SameLine();
		ImGui::Combo("on-mantle-hint", &cvar::yaw_on_mantle_hint, "disabled\0backwards\0jitter\0spin\0custom");
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(125);
		ImGui::SliderFloat("##1717", &cvar::custom_pitch, -69.9999999f, 69.9999999f, "%.1f");
		ImGui::PopItemWidth();

		ImGui::SameLine();
		if (ImGui::Button("-", ImVec2(18, 18)))
			cvar::custom_pitch -= 1.f;

		ImGui::SameLine();
		if (ImGui::Button("+", ImVec2(18, 18)))
			cvar::custom_pitch += 1.f;

		ImGui::SameLine();
		ImGui::Text("custom pitch angle");

		ImGui::PushItemWidth(125);
		ImGui::SliderFloat("##4", &cvar::custom_yaw, -360.f, 360.f, "%.1f");
		ImGui::PopItemWidth();

		ImGui::SameLine();
		if (ImGui::Button("-", ImVec2(18, 18)))
			cvar::custom_yaw -= 1.f;

		ImGui::SameLine();
		if (ImGui::Button("+", ImVec2(18, 18)))
			cvar::custom_yaw += 1.f;

		ImGui::SameLine();
		ImGui::Text("custom yaw angle");

		ImGui::Checkbox("mantle check", &cvar::anti_aim_mantle_check);
	}
}

void rendering_t::create_menu_imgui_visual_options(void)
{
	if (ImGui::CollapsingHeader("szn_players"))
	{
		ImGui::Checkbox("active##1", &cvar::player_visuals);
		ImGui::Separator();

		ImGui::PushItemWidth(125);
		ImGui::Combo("bounding box", &cvar::player_bounding_box_type, "disabled\0two_d\0corner");
		ImGui::PopItemWidth();

		ImGui::Checkbox("names", &cvar::player_names);
		ImGui::Checkbox("distance", &cvar::player_distance);
	}

	if (ImGui::CollapsingHeader("szn_local"))
	{
		ImGui::Checkbox("crosshair", &cvar::crosshair);

		ImGui::PushItemWidth(125);
		ImGui::SliderFloat("field of view", &cvar::field_of_view, 65.f, 160.f, "%.1f");
		ImGui::PopItemWidth();

		ImGui::Checkbox("third person", &cvar::cg_thirdperson);
		//ImGui::SameLine(300);
		//ImGui::Checkbox("extend", &cvar::thirdperson_extend_range);
		ImGui::PushItemWidth(125);
		ImGui::SliderFloat("third person range", &cvar::thirdperson_range, 65.f, 500.f, "%.1f");
		ImGui::PopItemWidth();

		ImGui::Checkbox("no recoil", &cvar::remove_recoil);
	}
}

void rendering_t::create_menu_imgui_misc_options(void)
{
	if (ImGui::CollapsingHeader("szn_misc"))
	{
		ImGui::Checkbox("spoof ip", &cvar::spoof_ip);
		ImGui::Checkbox("reload cancel", &cvar::reload_cancel);

		ImGui::PushItemWidth(125);
		ImGui::PopItemWidth();
	}
}

void rendering_t::create_menu_imgui_options(void)
{
	if (cvar::is_open)
	{
		if (ImGui::BeginTabBar("szn_tabs"))
		{
			if (ImGui::BeginTabItem("szn_aimbot"))
			{
				this->create_menu_imgui_aimbot_options();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("szn_visuals"))
			{
				this->create_menu_imgui_visual_options();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("szn_misc"))
			{
				this->create_menu_imgui_misc_options();
				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();
	}
}

void rendering_t::end_menu_imgui_instance(void)
{
	if (cvar::is_open)
		ImGui::End();
}

void rendering_t::begin_esp_imgui_instance(void)
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));

	// -- push an invis window so imgui will actually render the esp
	ImGui::Begin("RONMfySkveYzatb", (bool*)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
	ImGui::GetOverlayDrawList()->PushClipRectFullScreen();
}

void rendering_t::end_esp_imgui_instance(void)
{
	ImGui::End();
	ImGui::PopStyleColor(2);
}

rendering_t* render() { return &rendering_m; }