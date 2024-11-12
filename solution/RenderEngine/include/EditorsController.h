#pragma once

namespace sre
{

class ScenesManager;
class Scene;
class Entity;

class EditorsController
{
private:
	ScenesManager* scenesManager;

public:
	EditorsController(ScenesManager* arg_scenesManager);

	void loadScene();
	void saveScene();

	void createCube();
	void createPlane();

private:
	void createEntity(const char* name, const char* file);
	void notifyNewEntity(Entity* entity);
};

} // namespace
