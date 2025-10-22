#pragma once

#include "ASingleton.h"
#include "memory_aliases.h"
#include "EExecutionMode.h"
#include "ABaseMaterial.h"

#include <string>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace sre
{

class Entity;
class MeshComponent;
class GUIImageComponent;
class GUITextComponent;
class CameraComponent;
class GuizmoComponent;
class SkyboxComponent;

class MeshRenderer;
class ShadowRenderer;
class GUIRenderer;
class DebugRenderer;
class GuizmoRenderer;
class CustomRenderer;
class SkyboxRenderer;
class PostProcessingRenderer;

struct MeshData2D;

using StandardRendererMap = std::unordered_map<ABaseMaterial*, SPTR<MeshRenderer>, MaterialHash, MaterialEqual>;
using CustomRendererMap = std::unordered_map<ABaseMaterial*, SPTR<CustomRenderer>, MaterialHash, MaterialEqual>;

class RenderManager : ASingleton
{
private:
    class ShaderManager       *shaderManager;
    class AGraphicsWrapper    *graphicsWrapper;
    class LightManager        *lightManager;

	StandardRendererMap opaqueMeshRenderers;
    StandardRendererMap translucentMeshRenderers;
    CustomRendererMap customRenderers;
    SPTR<ShadowRenderer> shadowRenderer;
    SPTR<GUIRenderer> guiRenderer;
	SPTR<DebugRenderer> debugRenderer;
	SPTR<GuizmoRenderer> guizmoRenderer;
	SPTR<SkyboxRenderer> skyboxRenderer;
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
    void addMesh(StandardRendererMap& renderers, MeshComponent* mesh);
    void addMeshCustomMaterial(MeshComponent* mesh);
    void removeMesh(MeshComponent* mesh);
    void addGUIImageComponent(GUIImageComponent* guiComponent);
    void addGUITextComponent(GUITextComponent* guiComponent);
	void addGuizmoComponent(GuizmoComponent* guizmoComponent);
	void addDebugBox(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
    void addSkybox(SkyboxComponent* mesh);
	void reloadSkyboxMaterial(ABaseMaterial* newMaterial);
    void initGUIRenderer();
    void initShadowRenderer();

    void initPostProcessing();

    void setApplicationCamera(CameraComponent *camera);
    void setEditorCamera(CameraComponent* camera);
    void setExecutionMode(EExecutionMode::Type mode);
    CameraComponent* getCurrentCamera();

    void render();
    void renderGuizmos();

    static void DEBUG_drawTriangle();

    void setupBufferSubData(MeshData2D* meshData);
    void removeDestroyedEntities();
    void cleanUp();
    void cleanUpMeshes();
    void cleanUpGui();
    void cleanUpDebug();
    void cleanUpGuizmos();

    void setTargetFBO(uint32_t fbo);
    void unbindFrameBuffer();

friend class AScene;
friend class Scene;
friend class GUIScene;
friend class AtlasManager;
friend class CameraComponent;
friend class MeshComponent;
friend class SkyboxComponent;
friend class AExecutionStrategy;
friend class EditorStrategy;
friend class ApplicationStrategy;
friend class Material;
friend class GUITextComponent;
friend class SingletonsManager;
friend class BaseRendererShaderSetup;
friend class LightRendererShaderSetup;
friend class EditorSceneViewport;
friend class SceneViewportGuizmos;
friend class WorldEditor;
friend class ScenesManager;
};

} // namespace
