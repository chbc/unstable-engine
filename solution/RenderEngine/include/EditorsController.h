#pragma once

#include "memory_aliases.h"
#include "FileIcon.h"

#include <string>

namespace sre
{

class ScenesManager;
class Scene;
class Entity;

class EditorsController
{
private:
	ScenesManager* scenesManager = nullptr;

	const char* GUI_IMAGE_PATH = "engine\\media\\whiteTexture.png";

public:
	EditorsController(ScenesManager* arg_scenesManager);
	void newScene();
	void openScene();
	void openGui();
	void saveScene();
	void saveGui();
	void createGUIImage();
	void refreshFileIcons(std::string directoryPath, std::vector<UPTR<FileIcon>>& result);
	void saveEntity(Entity* entity);
	void loadFileFromBrowser(const char* filePath);
	void importMesh(const char* sourceFilePath, const char* destinationPath, float scaleFactor, std::string& resultFilePath);
	void createMeshEntity(const char* file, const char* meshName);
	void createDirectionalLight();
	void createPointLight();

private:
	void notifyNewEntity(Entity* entity);
};

} // namespace
