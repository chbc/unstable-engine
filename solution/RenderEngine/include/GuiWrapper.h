#pragma once
	#ifdef ENABLE_MEMORY_TRACKER
	#undef new 
#endif

#include "imgui.h" 

#ifdef ENABLE_MEMORY_TRACKER
#define new new(__FILE__, __LINE__)
#endif
