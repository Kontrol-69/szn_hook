#include "szn.h"

d3d_data_t d3d_data;

bool d3d::is_init;
IMGUI_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

HRESULT WINAPI d3d::end_scene(IDirect3DDevice9* Device)
{
	if (!d3d::is_init)
	{
		Device = Device;

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(FindWindow(NULL, L"Modern Warfare 2"));
		ImGui_ImplDX9_Init(Device);

		d3d::is_init = true;
	}

	render()->begin_imgui_frame();

	render()->begin_esp_imgui_instance();
	visuals()->create();
	render()->end_esp_imgui_instance();

	render()->begin_menu_imgui_instance();
	render()->create_menu_imgui_options();
	render()->end_menu_imgui_instance();

	render()->end_imgui_frame();

	return d3d_data.end_scene(Device);
}

HRESULT WINAPI d3d::reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	auto callback = d3d_data.reset(device, presentation);
	ImGui_ImplDX9_CreateDeviceObjects();

	return callback;
}

LRESULT CALLBACK hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (cvar::is_open)
	{
		if (ImGui::GetCurrentContext())
			ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

		ImGui::GetIO().MouseDrawCursor = 1;
		return true;
	}
	else
		ImGui::GetIO().MouseDrawCursor = 0;

	return CallWindowProc(d3d_data.wndproc, hWnd, uMsg, wParam, lParam);
}

void d3d::device_pointer(void)
{
	while (!d3d_data.device)
	{
		d3d_data.device = (DWORD)GetModuleHandle(L"d3d9.dll");
		Sleep(150);
	}

	d3d_data.pointer = memory(nullptr).pattern_scan(d3d_data.device, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");;
}

void d3d::get_vtable(void)
{
	if (!d3d_data.pointer)
		return;

	memcpy(&d3d_data.vtable, reinterpret_cast<void*>(d3d_data.pointer + 0x2), 0x4);
}

void d3d::create(void)
{
	d3d::device_pointer();
	d3d::get_vtable();

	d3d_data.end_scene = (d3d::end_scene_t)DetourFunction(reinterpret_cast<PBYTE>(d3d_data.vtable[0x2A]), reinterpret_cast<PBYTE>(d3d::end_scene));
	d3d_data.reset = (d3d::reset_t)DetourFunction(reinterpret_cast<PBYTE>(d3d_data.vtable[0x10]), reinterpret_cast<PBYTE>(d3d::reset));
	d3d_data.wndproc = (WNDPROC)SetWindowLongPtr(FindWindow(NULL, L"Modern Warfare 2"), GWL_WNDPROC, (LONG)hkWndProc);

	printf("szn_d3d_hooked\n");
}

void d3d::remove()
{
	DetourFunction(reinterpret_cast<PBYTE>(d3d_data.vtable[0x2A]), reinterpret_cast<PBYTE>(d3d_data.end_scene));
	DetourFunction(reinterpret_cast<PBYTE>(d3d_data.vtable[0x10]), reinterpret_cast<PBYTE>(d3d_data.reset));
	SetWindowLongPtr(FindWindowA(NULL, "Modern Warfare 2"), GWLP_WNDPROC, reinterpret_cast<LONG>(d3d_data.wndproc));

	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX9_Shutdown();
	ImGui::DestroyContext();

	printf("szn_d3d_removed\n");
}