#include "DefaultGameValues.h"
#include "FileUtils.h"
#include <vector>
#include <stdexcept>

namespace sre
{

Blackboard DefaultGameValues::blackboard;

void DefaultGameValues::load()
{
	FileUtils::initializeStoragePaths();

	const std::string FILE_PATH = "default_game.ini";

	std::vector<std::string> lines;
	FileUtils::loadConfigFile(FILE_PATH, lines);

	for (const std::string& item : lines)
	{
		size_t position = item.find('=');
		if (position != std::string::npos)
		{
			std::string key = item.substr(0, position);
			std::string strValue = item.substr(position + 1);

			int intValue{ 0 };
			float floatValue{ 0 };
			if (tryGetValue(strValue, intValue))
			{
				blackboard.set(key, intValue);
			}
			else if (tryGetValue(strValue, floatValue))
			{
				blackboard.set(key, floatValue);
			}
			else
			{
				blackboard.set(key, strValue);
			}
		}
	}
}

bool DefaultGameValues::tryGetValue(const std::string& input, int& result)
{
	if (input.find('.') == std::string::npos)
	{
		try
		{
			result = std::stoi(input);
			return true;
		}
		catch (...) { }
	}

	return false;
}

bool DefaultGameValues::tryGetValue(const std::string& input, float& result)
{
	try
	{
		result = std::stof(input);
		return true;
	}
	catch (...) {}

	return false;
}

} // namespace
