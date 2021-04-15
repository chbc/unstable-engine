#ifndef _ENGINE_VALUES_H_
#define _ENGINE_VALUES_H_

#include "core_defines.h"

#include <string>

namespace sre
{

struct SRE_API EngineValues
{
	static std::string APPLICATION_NAME;

	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static float ASPECT_RATIO;

	static void updateAspectRatio();
};

} // namespace

#endif
