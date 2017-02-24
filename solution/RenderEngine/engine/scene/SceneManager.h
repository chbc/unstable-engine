#ifndef _SCENE_MANAGER_H//
#define _SCENE_MANAGER_H_

#include <engine/entities/Entity.h>
#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/entities/components/lights/DirectionalLightComponent.h>
#include <engine/entities/components/lights/PointLightComponent.h>
#include <engine/entities/components/meshes/materials/EMaterialMap.h>

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
	
	VECTOR_UPTR<Entity> entities;

	int nodeCount;

	SceneManager();

public:
	~SceneManager();

	// renderables //
	Entity *createPlaneEntity(float size = 1.0f);
	Entity *createCubeEntity(float size = 1.0f);
	void addEntity(Entity *entity);

	// light //
	DirectionalLightComponent *addDirectionalLight();
	PointLightComponent *addPointLight();

	// camera //
	CameraComponent *getMainCamera();

private:
	int generateNodeId();

	friend class RenderEngine;
};

} // namespace
#endif
