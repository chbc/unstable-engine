#pragma once

#include "FileItem.h"
#include "memory_aliases.h"

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
	void refreshFileItems(const char* directoryPath, std::vector<UPTR<FileItem>>& result);

private:
	void createEntity(const char* name, const char* file);
	void notifyNewEntity(Entity* entity);
};

} // namespace
