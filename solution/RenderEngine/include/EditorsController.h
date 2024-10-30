#pragma once

namespace sre
{

class ScenesManager;
class Scene;

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
	void createMeshEntity(Scene* scene, const char* name, const char* filePath);
};

} // namespace
