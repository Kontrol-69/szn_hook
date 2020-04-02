#include "szn.h"

memory memory::write(const char* mem_cpy)
{
	VirtualProtect((void*)this->address, strlen(mem_cpy), PAGE_READWRITE, &this->p_virtual_protect);
	memcpy((void*)this->address, (void*)mem_cpy, strlen(mem_cpy));
	VirtualProtect((void*)this->address, strlen(mem_cpy), this->p_virtual_protect, &this->p_virtual_protect);

	return *this;
}

memory memory::read(char mem_type)
{
	switch (mem_type)
	{
	case 'i':
		printf("%i\n", *(int*)this->address);
		break;
	case 'f':
		printf("%.1f\n", *(float*)this->address);
		break;
	};

	return *this;
}

bool memory::compare_pattern(const BYTE* v1, const BYTE* v2, const char* v3)
{
	for (; *v3; ++v3, ++v1, ++v2)
		if (*v3 == 'x' && *v1 != *v2)
			return 0;

	return (*v3) == NULL;
}

DWORD memory::pattern_scan(DWORD address, DWORD length, BYTE* v1, const char* v2)
{
	for (DWORD i = 0; i < length; i++)
		if (this->compare_pattern((BYTE*)(address + i), v1, v2))
			return (DWORD)(address + i);

	return 0;
}