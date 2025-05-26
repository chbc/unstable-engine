#include "EngineValues.h"

namespace sre
{

std::string EngineValues::APPLICATION_NAME = "Unstable Engine";
int EngineValues::SCREEN_WIDTH = 1024;
int EngineValues::SCREEN_HEIGHT = 728;

float EngineValues::ASPECT_RATIO = static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT;

void EngineValues::updateAspectRatio()
{
	if ((SCREEN_WIDTH > 0) && (SCREEN_HEIGHT > 0))
	{
		ASPECT_RATIO = static_cast<float>(SCREEN_WIDTH) / SCREEN_HEIGHT;
	}
}

} // namespace
