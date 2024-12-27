#pragma once

#include <sstream>

namespace sre
{

namespace EContentType
{
	enum Type
	{
		ENGINE,
		CONTENT
	};
};

class Paths
{
private:
#ifdef __ANDROID__
	const char* CONTENT_SCENES_FOLDER = "content/es/scenes/";
	const char* CONTENT_MEDIA_FOLDER = "content/es/media/";

	const char* ENGINE_BASE_FOLDER = "engine/es/";
	const char* ENGINE_SCENES_FOLDER = "engine/es/scenes/";
	const char* ENGINE_MEDIA_FOLDER = "engine/es/media/";
	const char* ENGINE_ICONS_FOLDER = "engine/es/icons/";
#else
	const char* CONTENT_BASE_FOLDER = "../../content/";
	const char* CONTENT_SCENES_FOLDER = "../../content/scenes/";
	const char* CONTENT_MEDIA_FOLDER = "../../content/media/";

	const char* ENGINE_BASE_FOLDER = "../../engine/";
	const char* ENGINE_SCENES_FOLDER = "../../engine/scenes/";
	const char* ENGINE_MEDIA_FOLDER = "../../engine/media/";
	const char* ENGINE_ICONS_FOLDER = "../../engine/icons/";

#endif

public:
	void buildSceneFilePath(EContentType::Type contentType, const char* fileName, std::string& result);
	void buildMediaFilePath(EContentType::Type contentType, const char* fileName, std::string& result);
	void buildIconFilePath(const char* fileName, std::string& result);
	void buildFilePath(const char* basePath, const char* fileName, const char* extension, std::string& result);

friend class EditorFileBrowser;
};

} // namespace sre
