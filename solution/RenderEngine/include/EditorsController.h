#pragma once

#include "memory_aliases.h"
#include "FileIcon.h"

#include <string>

namespace sre
{

class ScenesManager;
class Scene;
class Entity;
class TextureManager;

class EditorsController
{
private:
	ScenesManager* scenesManager = nullptr;
	TextureManager* textureManager = nullptr;

public:
	EditorsController(ScenesManager* arg_scenesManager);
	void init();
	void loadScene();
	void saveScene();
	void createCube();
	void createPlane();
	void refreshFileIcons(std::string directoryPath, std::vector<UPTR<FileIcon>>& result);

private:
	void createEntity(const char* name, const char* file);
	void notifyNewEntity(Entity* entity);
};

} // namespace
