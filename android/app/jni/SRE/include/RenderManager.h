#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include "ASingleton.h"
#include "memory_aliases.h"
#include <string>

namespace sre
{

class MeshComponent;
class GUIImageComponent;
class CameraComponent;
class Texture;
class MeshRenderer;
class Entity;
class DirectionalLightComponent;
class PointLightComponent;

struct GUIVertexData;
struct MeshData;
struct GUIMeshData;

/*!
	Singleton Class to handle renders
*/
class RenderManager : ASingleton
{

private:
    class ShaderManager       *shaderManager;
    class AGraphicsWrapper    *graphicsWrapper;
    class LightManager        *lightManager;

	VECTOR_UPTR<MeshRenderer> opaqueMeshRenderers;
    VECTOR_UPTR<MeshRenderer> translucentMeshRenderers;
    UPTR<class ShadowRenderer> shadowRenderer;
    UPTR<class GUIRenderer> guiRenderer;
	UPTR<class PostProcessingRenderer> postProcessingRenderer;

    CameraComponent *mainCamera;

private:
    RenderManager();

protected:
    void init() override;
    void preRelease() override;

private:
    void addEntity(Entity* entity);
    void addMesh(MeshComponent* mesh);
    void addMesh(VECTOR_UPTR<MeshRenderer>& renderers, MeshComponent* mesh);
    void addGUIComponent(GUIImageComponent* guiComponent);
    void addDynamicGUIComponent(GUIImageComponent* guiComponent);
    void initGUIRenderer();
    void initShadowRenderer();

    void onSceneLoaded();

    void setMainCamera(CameraComponent *camera);
    CameraComponent *getMainCamera();

    void render();

    static void DEBUG_drawTriangle();

    DirectionalLightComponent *addDirectionalLight(Entity *entity);
    PointLightComponent *addPointLight(Entity *entity);

    void setupBufferSubData(GUIMeshData* meshData);
    void onRemoveDestroyedEntities();

friend class AEntityManager;
friend class SceneManager;
friend class AtlasManager;
friend class MeshComponent;
friend class RenderEngine;
friend class Material;
friend class GUITextComponent;
friend class SingletonsManager;
friend class BaseRendererShaderSetup;
};

} // namespace
#endif
