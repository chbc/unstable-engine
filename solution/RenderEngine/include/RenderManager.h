#pragma once

#include "ASingleton.h"
#include "memory_aliases.h"
#include <string>
#include "EExecutionMode.h"

namespace sre
{

class Entity;
class MeshComponent;
class GUIImageComponent;
class CameraComponent;

class MeshRenderer;
class ShadowRenderer;
class GUIRenderer;
class PostProcessingRenderer;

struct MeshData2D;

/*!
	Singleton Class to handle renders
*/
class RenderManager : ASingleton
{

private:
    class ShaderManager       *shaderManager;
    class AGraphicsWrapper    *graphicsWrapper;
    class LightManager        *lightManager;

	VECTOR_SPTR<MeshRenderer> opaqueMeshRenderers;
    VECTOR_SPTR<MeshRenderer> translucentMeshRenderers;
    SPTR<ShadowRenderer> shadowRenderer;
    SPTR<GUIRenderer> guiRenderer;
	SPTR<PostProcessingRenderer> postProcessingRenderer;

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
    void addMesh(VECTOR_SPTR<MeshRenderer>& renderers, MeshComponent* mesh);
    void removeMesh(MeshComponent* mesh);
    void addGUIComponent(GUIImageComponent* guiComponent);
    void addDynamicGUIComponent(GUIImageComponent* guiComponent);
    void initGUIRenderer();
    void initShadowRenderer();

    void initPostProcessing();

    void setApplicationCamera(CameraComponent *camera);
    void setEditorCamera(CameraComponent* camera);
    void setExecutionMode(EExecutionMode::Type mode);
    CameraComponent* getCurrentCamera();

    void render();

    static void DEBUG_drawTriangle();

    void setupBufferSubData(MeshData2D* meshData);
    void removeDestroyedEntities();
    void cleanUp();
    void cleanUpMeshes();
    void cleanUpGui();

    void setTargetFBO(uint32_t fbo);
    void unbindFrameBuffer();

friend class AScene;
friend class Scene;
friend class GUIScene;
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
friend class LightRendererShaderSetup;
friend class EditorSceneViewport;
friend class WorldEditor;
friend class ScenesManager;
};

} // namespace
