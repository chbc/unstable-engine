#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "AEntityManager.h"
#include "CameraComponent.h"
#include "DirectionalLightComponent.h"
#include "PointLightComponent.h"
#include "PrimitiveMeshFactory.h"

namespace sre
{

/*!
    Class for manager scene nodes.
*/
class SceneManager : public AEntityManager
{
private:
    SceneManager();

public:
    // renderables //
    SRE_API Entity *createPlaneEntity(float size = 1.0f);
    SRE_API Entity *createCubeEntity(float size = 1.0f);
    SRE_API Entity *createModelEntity(const std::string &fileName);

    // light //
    SRE_API DirectionalLightComponent *addDirectionalLight();
    SRE_API PointLightComponent *addPointLight();

    // camera //
    SRE_API class CameraComponent *getMainCamera();
    SRE_API Entity *createMeshEntity(MeshData<VertexData> *objectData);

friend class RenderEngine;
};

} // namespace
#endif
