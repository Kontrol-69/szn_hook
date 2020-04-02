namespace d3d
{
	extern bool is_init;

	using end_scene_t = std::add_pointer_t<HRESULT WINAPI(IDirect3DDevice9* device)>;
	using reset_t = std::add_pointer_t<HRESULT WINAPI(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*)>;

	extern HRESULT WINAPI end_scene(IDirect3DDevice9* device);
	extern HRESULT WINAPI reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation);
	
	extern void device_pointer(void);
	extern void get_vtable(void);

	extern void create(void);
	extern void remove(void);
}

struct d3d_data_t
{
	DWORD* vtable;
	DWORD device;
	DWORD pointer;

	d3d::end_scene_t end_scene;
	d3d::reset_t reset;

	WNDPROC wndproc;
}; extern d3d_data_t d3d_data;