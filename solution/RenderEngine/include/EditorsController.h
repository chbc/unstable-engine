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

public:
	EditorsController(ScenesManager* arg_scenesManager);
	void loadScene();
	void saveScene();
	void createCube();
	void createPlane();
	void createSphere();
	void refreshFileIcons(std::string directoryPath, std::vector<UPTR<FileIcon>>& result);

private:
	void createEntity(const char* name, const char* file);
	void notifyNewEntity(Entity* entity);
};

} // namespace
