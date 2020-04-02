#include "szn.h"

cg_s* cg;
entity_t* entity;
clientactive_t* clientactive;
uicontext_t uicontext;
refdef_t* refdef;
trace_t trace;

void load_structs(void)
{
	cg = reinterpret_cast<cg_s*>(0x8A0ED0);
	entity = reinterpret_cast<entity_t*>(0x9A4110);
	clientactive = reinterpret_cast<clientactive_t*>(0xBC4520);
	uicontext = *reinterpret_cast<uicontext_t*>(0x627AA18);
	refdef = reinterpret_cast<refdef_t*>(0x90B648);
}