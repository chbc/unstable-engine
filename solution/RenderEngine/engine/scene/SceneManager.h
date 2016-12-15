#ifndef _SCENE_MANAGER_H//
#define _SCENE_MANAGER_H_

/*
#include <engine/entities/CameraNode.h>
#include <engine/entities/renderables/RenderableNode.h>
#include <engine/entities/lights/DirectionalLight.h>
#include <engine/entities/lights/PointLight.h>
#include <engine/utils/singleton_macros.h>
*/

#include <engine/entities/Entity.h>

namespace sre
{

class RenderEngine;

/*!
	Class for manager scene nodes.
*/
class SceneManager
{
// ### DECLARE_SINGLETON(SceneManager);

private:
	UPTR<Entity> mainCamera;
	VECTOR_UPTR<Entity> entities;

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
	Entity *getMainCamera();

private:
	void render();
	int generateNodeId();

	friend class RenderEngine;
};

} // namespace
#endif
