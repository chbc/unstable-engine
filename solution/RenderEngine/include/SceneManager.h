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
    SRE_API Entity* createPerspectiveCamera(float fov = 100.0f, float near = 0.1f, float far = 1000.0f, Entity* parent = nullptr);
    SRE_API Entity* createOrthoCamera(Entity* parent = nullptr);

    // renderables //
    SRE_API Entity* createPlaneEntity(const glm::vec2& size, float tileMultiplier = 1.0f, const std::string& name = "", Entity* parent = nullptr);
    SRE_API Entity *createCubeEntity(float size = 1.0f, const std::string& name = "", Entity* parent = nullptr);
    SRE_API Entity *createModelEntity(const std::string &fileName, const std::string& name = "", Entity* parent = nullptr);

    // light //
    SRE_API DirectionalLightComponent* createDirectionalLight(const std::string& name = "", Entity* parent = nullptr);
    SRE_API PointLightComponent* createPointLight(const std::string& name = "", Entity* parent = nullptr);

    // camera //
    SRE_API class CameraComponent *getMainCamera();
    SRE_API Entity *createMeshEntity(MeshData* objectData, const std::string& name = "", Entity* parent = nullptr);

friend class RenderEngine;
};

} // namespace
#endif
