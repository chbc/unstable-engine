#ifndef _SCENE_MANAGER_H//
#define _SCENE_MANAGER_H_

#include <engine/entities/Entity.h>
#include <engine/entities/components/cameras/CameraComponent.h>

namespace sre
{

class RenderManager;
class CameraComponent;

/*!
	Class for manager scene nodes.
*/
class SceneManager
{
private:
	UPTR<Entity> mainCamera;
	VECTOR_UPTR<Entity> renderableEntities;

	int nodeCount;

	SceneManager();

public:
	~SceneManager();

	// renderables //
	Entity *addCubeEntity(float size = 1);
	Entity *addPlaneEntity(float size = 1);
	Entity *addModelEntity(const char *fileName);

	// light //
	Entity *addDirectionalLight();
	Entity *addPointLight();

	// camera //
	CameraComponent *getMainCamera();

private:
	void render(RenderManager *renderManager);
	int generateNodeId();

	friend class RenderEngine;
};

} // namespace
#endif
