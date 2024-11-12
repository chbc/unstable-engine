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
};

} // namespace
