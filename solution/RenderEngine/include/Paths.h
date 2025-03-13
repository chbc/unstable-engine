#pragma once

#include <sstream>

namespace sre
{

class Paths
{
public:
#ifdef __ANDROID__
	const char* GAME_BASE_FOLDER = "content/game/es/";

	const char* ENGINE_BASE_FOLDER = "content/engine/es/";
	const char* ENGINE_SCENES_FOLDER = "content/engine/es/scenes/";
	const char* ENGINE_MEDIA_FOLDER = "content/engine/es/media/";
	const char* ENGINE_ICONS_FOLDER = "content/engine/es/icons/";
#else
	const char* GAME_BASE_FOLDER = "../content/game/";

	const char* ENGINE_BASE_FOLDER = "../content/engine/";
	const char* ENGINE_SCENES_FOLDER = "../content/engine/scenes/";
	const char* ENGINE_MEDIA_FOLDER = "../content/engine/media/";
	const char* ENGINE_ICONS_FOLDER = "../content/engine/icons/";
#endif

public:
	void buildSceneFilePath(const char* fileName, std::string& result, bool checkFileExists = true);
	void buildMediaFilePath(const char* fileName, std::string& result, bool checkFileExists = true);
	void buildIconFilePath(const char* fileName, std::string& result);
	void buildFilePath(const char* basePath, const char* fileName, const char* extension, std::string& result);
};

} // namespace sre
