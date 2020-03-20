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
    class MatrixManager       *matrixManager;
    class LightManager        *lightManager;
    class TextureManager      *textureManager;
    
    VECTOR_UPTR<class MeshRenderer> renders;
    UPTR<class ShadowRenderer> shadowRenderer;
    UPTR<class GUIRenderer> guiRenderer;
	UPTR<class PostProcessingRenderer> postProcessingRenderer;

    CameraComponent *mainCamera;

	uint32_t screenWidth;
	uint32_t screenHeight;

private:
    RenderManager();

protected:
    void init();
    void release() {}

private:
    void addEntity(Entity *entity);
    void addMesh(MeshComponent *mesh);
    void addGUIComponent(GUIImageComponent *guiComponent);
    void addDynamicGUIComponent(GUIImageComponent *guiComponent);
    void initGUIRenderer();
    void initShadowRenderer();

    void onSceneLoaded();

    void setMainCamera(CameraComponent *camera);
    CameraComponent *getMainCamera();

    void render();
    void updateViewMatrix();

    static void DEBUG_drawTriangle();

    DirectionalLightComponent *addDirectionalLight(Entity *entity);
    PointLightComponent *addPointLight(Entity *entity);

    Texture *loadGUITexture(const std::string &fileName);
    Texture *loadDiffuseTexture(const std::string &fileName);
    Texture *loadNormalTexture(const std::string &fileName);
    Texture *loadSpecularTexture(const std::string &fileName);
    Texture *loadAOTexture(const std::string &fileName);

    void setupBufferSubData(GUIMeshData* meshData);
    void removeDestroyedEntities();

friend class AEntityManager;
friend class SceneManager;
friend class AtlasManager;
friend class MeshComponent;
friend class RenderEngine;
friend class Material;
friend class GUIImageComponent;
friend class GUITextComponent;
friend class DiffuseMaterialComponent;
friend class NormalMaterialComponent;
friend class SpecularMaterialComponent;
friend class AmbientOcclusionMaterialComponent;
friend class SingletonsManager;
};

} // namespace
#endif
