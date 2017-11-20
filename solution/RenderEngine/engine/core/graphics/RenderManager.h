#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include <glm/vec3.hpp>
#include <engine/core/singletonsManager/ASingleton.h>
#include <engine/utils/memory_aliases.h>

namespace sre
{
class MeshComponent;
class GUIImageComponent;
class CameraComponent;
class AGraphicsWrapper;
class MatrixManager;
class ShaderManager;
class LightManager;
class TextureManager;
class Texture;

class Entity;
class DirectionalLightComponent;
class PointLightComponent;

class Renderer;
class GUIRenderer;

struct GUIVertexData;
template <typename T> struct MeshData;

/*!
	Singleton Class to handle renders
*/
class RenderManager : ASingleton
{

private:
    SPTR<ShaderManager> shaderManager;
    SPTR<AGraphicsWrapper> graphicsWrapper;
    MatrixManager *matrixManager;
    UPTR<LightManager> lightManager;
    UPTR<TextureManager> textureManager;
    
    VECTOR_UPTR<Renderer> renders;
    UPTR<GUIRenderer> guiRenderer;
    
    CameraComponent *mainCamera;

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

    void setMainCamera(CameraComponent *camera);
    CameraComponent *getMainCamera();

    void render();
    void renderCamera();

    static void DEBUG_drawTriangle();
    void clearBuffer();

    DirectionalLightComponent *addDirectionalLight(Entity *entity);
    PointLightComponent *addPointLight(Entity *entity);

    Texture *loadGUITexture(const std::string &fileName);
    Texture *loadDiffuseTexture(const std::string &fileName);
    Texture *loadNormalTexture(const std::string &fileName);
    Texture *loadSpecularTexture(const std::string &fileName);
    Texture *loadAOTexture(const std::string &fileName);

    void setupBufferSubData(const GUIImageComponent *guiComponent);

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
