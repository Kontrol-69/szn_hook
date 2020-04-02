class memory
{
private:
	void* address;
	DWORD p_virtual_protect;
public:
	memory(void* address) { this->address = address; }
	memory write(const char* mem_cpy);
	memory read(char mem_type);

	bool compare_pattern(const BYTE* v1, const BYTE* v2, const char* v3);
	DWORD pattern_scan(DWORD address, DWORD length, BYTE* v1, const char* v2);
};