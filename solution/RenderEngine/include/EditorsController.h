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
	std::string cubeMeshPath;
	std::string planeMeshPath;
	std::string sphereMeshPath;
	std::string guiImagePath;

public:
	EditorsController(ScenesManager* arg_scenesManager);
	void openScene();
	void openGui();
	void saveScene();
	void saveGui();
	void createCube();
	void createPlane();
	void createSphere();
	void createGUIImage();
	void refreshFileIcons(std::string directoryPath, std::vector<UPTR<FileIcon>>& result);
	void saveEntity(Entity* entity);
	void loadFileFromBrowser(const char* filePath);

private:
	void createMeshEntity(const char* name, const char* file, const char* meshName = "");
	void notifyNewEntity(Entity* entity);
};

} // namespace
