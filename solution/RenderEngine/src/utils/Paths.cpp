#include "Paths.h"
#include "FileUtils.h"

namespace sre
{

void Paths::buildSceneFilePath(const char* fileName, std::string& result, bool checkFileExists)
{
	this->buildFilePath(CONTENT_SCENES_FOLDER, fileName, ".scene", result);
	if (checkFileExists && !FileUtils::fileExists(result))
	{
		this->buildFilePath(ENGINE_SCENES_FOLDER, fileName, ".scene", result);
	}
}

void Paths::buildMediaFilePath(const char* fileName, std::string& result, bool checkFileExists)
{
	this->buildFilePath(CONTENT_MEDIA_FOLDER, fileName, "", result);
	if (checkFileExists && !FileUtils::fileExists(result))
	{
		this->buildFilePath(ENGINE_MEDIA_FOLDER, fileName, "", result);
	}
}

void Paths::buildIconFilePath(const char* fileName, std::string& result)
{
	this->buildFilePath(ENGINE_ICONS_FOLDER, fileName, ".png", result);
}

void Paths::buildFilePath(const char* basePath, const char* fileName, const char* extension, std::string& result)
{
	std::ostringstream stream;
	stream << basePath << fileName << extension;
	result = stream.str();
}

} // namespace
