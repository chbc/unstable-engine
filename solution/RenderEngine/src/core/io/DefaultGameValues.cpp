#include "DefaultGameValues.h"
#include "FileUtils.h"
#include <vector>

namespace sre
{

Blackboard DefaultGameValues::blackboard;

void DefaultGameValues::load()
{
#ifdef __ANDROID__
	const std::string FILE_NAME = "config/default_game.ini";
#else
	const std::string FILE_NAME = "../../config/default_game.ini";
#endif

	std::vector<std::string> lines;
	FileUtils::loadFile(FILE_NAME, lines);

	for (const std::string& item : lines)
	{
		size_t position = item.find('=');
		if (position != std::string::npos)
		{
			std::string key = item.substr(0, position);
			std::string value = item.substr(position + 1);

			if (key == "START_UP_SCENE")
			{
#ifdef __ANDROID__
				const std::string BASE_FOLDER = "scenes/";
#else
				const std::string BASE_FOLDER = "../../scenes/";
#endif
				std::string sceneValue = BASE_FOLDER + value + ".scene";
				blackboard.set("START_UP_SCENE", sceneValue);
			}
		}
	}
}

} // namespace
