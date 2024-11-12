#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include "ASingleton.h"
#include "memory_aliases.h"
#include <string>
#include "PostProcessingRenderer.h"
#include "GUIRenderer.h"
#include "ShadowRenderer.h"
#include "MeshRenderer.h"
#include "EExecutionMode.h"

namespace sre
{

class MeshComponent;
class GUIImageComponent;
class CameraComponent;

class Entity;
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
    UPTR<GUIRenderer> guiRenderer;
	UPTR<PostProcessingRenderer> postProcessingRenderer;

    CameraComponent* applicationCamera{ nullptr };
    CameraComponent* editorCamera{ nullptr };
    CameraComponent* currentCamera{ nullptr };
    uint32_t targetFBO{ 0 };

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

    void initRenderers();
    void initPostProcessing();

    void setApplicationCamera(CameraComponent *camera);
    void setEditorCamera(CameraComponent* camera);
    void setExecutionMode(EExecutionMode::Type mode);
    CameraComponent* getCurrentCamera();

    void render();

    static void DEBUG_drawTriangle();

    void setupBufferSubData(GUIMeshData* meshData);
    void removeDestroyedEntities();
    void cleanUp();

    void setTargetFBO(uint32_t fbo);
    void unbindFrameBuffer();

friend class AScene;
friend class Scene;
friend class AtlasManager;
friend class CameraComponent;
friend class MeshComponent;
friend class AExecutionStrategy;
friend class EditorStrategy;
friend class ApplicationStrategy;
friend class Material;
friend class GUITextComponent;
friend class SingletonsManager;
friend class BaseRendererShaderSetup;
friend class EditorSceneViewport;
friend class WorldEditor;
};

} // namespace
#endif
