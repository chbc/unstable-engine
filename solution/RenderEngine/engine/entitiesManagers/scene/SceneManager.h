#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "../AEntityManager.h"
#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/entities/components/lights/DirectionalLightComponent.h>
#include <engine/entities/components/lights/PointLightComponent.h>
#include <engine/core/graphics/meshData/PrimitiveMeshFactory.h>

namespace sre
{

/*!
    Class for manager scene nodes.
*/
class SRE_API SceneManager : public AEntityManager
{
private:
    SceneManager();

public:
    // renderables //
    Entity *createPlaneEntity(float size = 1.0f);
    Entity *createCubeEntity(float size = 1.0f);
    Entity *createModelEntity(const std::string &fileName);

    // light //
    DirectionalLightComponent *addDirectionalLight();
    PointLightComponent *addPointLight();

    // camera //
    class CameraComponent *getMainCamera();
    Entity *createMeshEntity(MeshData<VertexData> *objectData);

friend class RenderEngine;
};

} // namespace
#endif
