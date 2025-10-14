#include "RenderManager.h"
#include "Entity.h"
#include "MeshComponent.h"
#include "Material.h"
#include "GUIImageComponent.h"
#include "GUITextComponent.h"
#include "CameraComponent.h"
#include "GuizmoComponent.h"
#include "SkyboxComponent.h"
#include "SingletonsManager.h"
#include "MeshData.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "PostProcessingComponent.h"
#include "EngineValues.h"
#include "AGraphicsWrapper.h"
#include "MeshRenderer.h"
#include "CustomRenderer.h"
#include "PostProcessingRenderer.h"
#include "GUIRenderer.h"
#include "DebugRenderer.h"
#include "GuizmoRenderer.h"
#include "ShadowRenderer.h"
#include "SkyboxRenderer.h"
#include "CollectionsUtils.h"

namespace sre
{

void RenderManager::init()
{
    SingletonsManager *singletonsManager = SingletonsManager::getInstance();
    this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
    this->lightManager      = singletonsManager->get<LightManager>();
    this->shaderManager     = singletonsManager->get<ShaderManager>();
}

void RenderManager::preRelease()
{
    this->cleanUp();
}

void RenderManager::addEntity(Entity *entity)
{
    if (entity->hasComponent<SkyboxComponent>())
    {
        SkyboxComponent* mesh = entity->getComponent<SkyboxComponent>();
        this->addSkybox(mesh);
    }
	else if (entity->hasComponent<MeshComponent>())
    {
        MeshComponent *mesh = entity->getComponent<MeshComponent>();
        this->addMesh(mesh);
    }
    else if (entity->hasComponent<GUIImageComponent>())
    {
        GUIImageComponent *guiComponent = entity->getComponent<GUIImageComponent>();
        this->addGUIImageComponent(guiComponent);
    }
    else if (entity->hasComponent<GUITextComponent>())
    {
        GUITextComponent *guiComponent = entity->getComponent<GUITextComponent>();
        this->addGUITextComponent(guiComponent);
    }
    else if (entity->hasComponent<CameraComponent>())
    {
        CameraComponent* newCamera = entity->getComponent<CameraComponent>();
        if ((this->applicationCamera == nullptr) || newCamera->isApplicationCamera && newCamera->isMainCamera)
        {
            this->applicationCamera = newCamera;
            
            if (this->currentCamera == nullptr)
            {
                this->currentCamera = newCamera;
            }
        }
    }
    
    size_t size = entity->getChildrenCount();
    for (size_t i = 0; i < size; i++)
    {
        this->addEntity(entity->getChild(i));
    }
}

void RenderManager::addMesh(MeshComponent* mesh)
{
    if (mesh->isMaterialStandard())
    {
        if (mesh->isOpaque())
        {
            this->addMesh(this->opaqueMeshRenderers, mesh);
        }
        else
        {
            this->addMesh(this->translucentMeshRenderers, mesh);
        }

        if (static_cast<Material*>(mesh->getMaterial())->getCastShadow())
        {
            this->initShadowRenderer();
            this->shadowRenderer->addItem(mesh);
        }
    }
    else
    {
        this->addMeshCustomMaterial(mesh);
    }
}

void RenderManager::addMesh(StandardRendererMap& renderers, MeshComponent* mesh)
{
    ABaseMaterial* material = mesh->getMaterial();
    MeshRenderer* renderer{ nullptr };
    if (renderers.count(material) > 0)
    {
        renderer = renderers[material].get();
	}
    else
    {
        renderer = new MeshRenderer{ material, this->shaderManager, this->graphicsWrapper };
		renderers[material] = SPTR<MeshRenderer>(renderer);
        renderer->init(false, false);
    }

    renderer->addMesh(mesh);
}

void RenderManager::addMeshCustomMaterial(MeshComponent* mesh)
{
    ABaseMaterial* material = mesh->getMaterial();
    CustomRenderer* renderer{ nullptr };
    if (this->customRenderers.count(material) > 0)
    {
        renderer = this->customRenderers[material].get();
    }
    else
    {
        renderer = new CustomRenderer{ material, this->shaderManager, this->graphicsWrapper };
        this->customRenderers[material] = SPTR<CustomRenderer>(renderer);
        renderer->init();
    }

    renderer->addMesh(mesh);
}

void RenderManager::removeMesh(MeshComponent* mesh)
{
    bool meshRemoved = false;

    StandardRendererMap::iterator it;
    for (it = this->opaqueMeshRenderers.begin(); it != this->opaqueMeshRenderers.end(); ++it)
    {
        if ((it)->second->removeMesh(mesh))
        {
            meshRemoved = true;
            break;
        }
    }

	if (!meshRemoved)
	{
		for (it = this->translucentMeshRenderers.begin(); it != this->translucentMeshRenderers.end(); ++it)
		{
            if ((it)->second->removeMesh(mesh))
			{
				meshRemoved = true;
				break;
			}
		}
	}

	if (!meshRemoved)
	{
		for (auto& item : this->customRenderers)
		{
			if (item.second->removeMesh(mesh))
			{
				meshRemoved = true;
				break;
			}
		}
	}

    CollectionsUtils::removeIfRendererIsEmpty(this->opaqueMeshRenderers);
    CollectionsUtils::removeIfRendererIsEmpty(this->translucentMeshRenderers);
	CollectionsUtils::removeIfRendererIsEmpty(this->customRenderers);
}

void RenderManager::addGUIImageComponent(GUIImageComponent *guiComponent)
{
    if (guiComponent->isAbleToBeRendered())
    {
        this->initGUIRenderer();
        this->guiRenderer->addImageComponent(guiComponent);
    }
}

void RenderManager::addGUITextComponent(GUITextComponent*guiComponent)
{
    this->initGUIRenderer();
    this->guiRenderer->addTextComponent(guiComponent);
}

void RenderManager::addGuizmoComponent(GuizmoComponent* guizmoComponent)
{
	if (!this->guizmoRenderer)
	{
		this->guizmoRenderer = SPTR<GuizmoRenderer>{ new GuizmoRenderer{this->shaderManager, this->graphicsWrapper} };
		this->guizmoRenderer->loadShader();
	}
	this->guizmoRenderer->addGuizmo(guizmoComponent);
}

void RenderManager::addDebugBox(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
{
	if (!this->debugRenderer)
	{
		this->debugRenderer = SPTR<DebugRenderer>{ new DebugRenderer{this->shaderManager, this->graphicsWrapper} };
		this->debugRenderer->loadShader();
	}

	this->debugRenderer->addBox(position, size, color);
}

void RenderManager::addSkybox(SkyboxComponent* mesh)
{
    if (!this->skyboxRenderer)
    {
        this->skyboxRenderer = SPTR<SkyboxRenderer>{ new SkyboxRenderer{ mesh->getMaterial(), this->shaderManager, this->graphicsWrapper } };
        this->skyboxRenderer->init();
	}

	this->skyboxRenderer->addMesh(mesh);
}

void RenderManager::initGUIRenderer()
{
    if (!this->guiRenderer)
    {
        this->guiRenderer = SPTR<GUIRenderer>{ new GUIRenderer{this->shaderManager, this->graphicsWrapper} };
        this->guiRenderer->loadShader();
    }
}

void RenderManager::initShadowRenderer()
{
    if (!this->shadowRenderer)
    {
        this->shadowRenderer = SPTR<ShadowRenderer>{ new ShadowRenderer };
        this->shadowRenderer->init();
    }
}

void RenderManager::initPostProcessing()
{
    /*
    bool useBrightnessSegmentation = false;
    bool includeDepth = false;
    Entity* cameraEntity = this->currentCamera->getEntity();
    if (cameraEntity->hasComponent<PostProcessingComponent>())
    {
        PostProcessingComponent* postProcessingComponent = cameraEntity->getComponent<PostProcessingComponent>();
        this->postProcessingRenderer = SPTR<PostProcessingRenderer>{ new PostProcessingRenderer };
        this->postProcessingRenderer->onSceneLoaded(postProcessingComponent);

        useBrightnessSegmentation = this->postProcessingRenderer->isUsingBrightnessSegmentation();
        includeDepth = this->postProcessingRenderer->isIncludingDepth();
    }
    */
}

void RenderManager::setApplicationCamera(CameraComponent* camera)
{
    this->applicationCamera = camera;
}

void RenderManager::setEditorCamera(CameraComponent* camera)
{
    this->editorCamera = camera;
}

void RenderManager::setExecutionMode(EExecutionMode::Type mode)
{
    this->currentCamera = (mode == EExecutionMode::APPLICATION) ? this->applicationCamera : this->editorCamera;
}

CameraComponent* RenderManager::getCurrentCamera()
{
    return this->currentCamera;
}

void RenderManager::render()
{
    // Depth rendering
    if (this->shadowRenderer.get() != nullptr)
        this->shadowRenderer->render();

    // Scene rendering
    uint32_t fbo = this->targetFBO;
    if (this->postProcessingRenderer.get() != nullptr)
        fbo = this->postProcessingRenderer->getFirstPassFBO();
    
    this->graphicsWrapper->bindFrameBuffer(fbo);

    this->graphicsWrapper->setViewport(EngineValues::SCREEN_WIDTH, EngineValues::SCREEN_HEIGHT);
    this->graphicsWrapper->clearColorAndDepthBuffer();

    if (this->currentCamera != nullptr)
    {
        this->currentCamera->updateView();

        // Opaque meshes rendering
        for (const auto& item : this->opaqueMeshRenderers)
        {
            item.second->render();
        }

        // Custom meshes rendering
        for (const auto& item : this->customRenderers)
        {
            item.second->render(this->currentCamera);
        }

        // Translucent meshes rendering
        for (const auto& item : this->translucentMeshRenderers)
        {
            item.second->render();
        }

		// Skybox rendering
        if (this->skyboxRenderer.get() != nullptr)
        {
			this->skyboxRenderer->render(this->currentCamera);
		}
    }

	// Post processing rendering
    if (this->postProcessingRenderer.get() != nullptr)
    {
        this->postProcessingRenderer->onPostRender(this->targetFBO);
    }

    // Debug rendering
    if (this->debugRenderer.get() != nullptr)
    {
        this->debugRenderer->render(this->currentCamera);
    }

    // GUI rendering
    if (this->guiRenderer.get() != nullptr)
    {
        this->guiRenderer->render();
    }
}

void RenderManager::renderGuizmos()
{
    this->graphicsWrapper->disableDepthTest();

	if (this->guizmoRenderer.get() && this->currentCamera)
	{
		this->guizmoRenderer->render(this->currentCamera);
	}

	this->graphicsWrapper->enableDepthTest();
}

void RenderManager::DEBUG_drawTriangle()
{
/*
#ifndef __ANDROID__
    OpenGLAPI::DEBUG_drawTriangle();
#endif
*/
}

void RenderManager::setupBufferSubData(MeshData2D* meshData)
{
    this->graphicsWrapper->bindVAO(meshData->vao, meshData->vbo);
    this->graphicsWrapper->setupBufferSubData(meshData);
}

void RenderManager::removeDestroyedEntities()
{
    for (const auto& item : this->opaqueMeshRenderers)
    {
        item.second->removeDestroyedEntities();
    }

    for (const auto& item : this->translucentMeshRenderers)
    {
        item.second->removeDestroyedEntities();
    }

    CollectionsUtils::removeIfRendererIsEmpty(this->opaqueMeshRenderers);
    CollectionsUtils::removeIfRendererIsEmpty(this->translucentMeshRenderers);

	for (const auto& item : this->customRenderers)
	{
		item.second->removeDestroyedEntities();
	}

    CollectionsUtils::removeIfRendererIsEmpty(this->customRenderers);

    if (this->guiRenderer.get() != nullptr)
    {
        this->guiRenderer->removeDestroyedEntities();
        if (this->guiRenderer->isEmpty())
            this->guiRenderer = nullptr;
    }

    this->lightManager->removeDestroyedEntities();
}

void RenderManager::cleanUp()
{
    this->cleanUpMeshes();
    this->cleanUpGui();
    this->cleanUpDebug();
	this->cleanUpGuizmos();

    this->currentCamera = nullptr;
}

void RenderManager::cleanUpMeshes()
{
    this->lightManager->cleanUp();
    this->opaqueMeshRenderers.clear();
    this->translucentMeshRenderers.clear();
    this->customRenderers.clear();
}

void RenderManager::cleanUpGui()
{
	if (this->guiRenderer)
	{
		this->guiRenderer.reset();
	}
}

void RenderManager::cleanUpDebug()
{
    if (this->debugRenderer)
    {
        this->debugRenderer.reset();
    }
}

void RenderManager::cleanUpGuizmos()
{
	if (this->guizmoRenderer)
	{
		this->guizmoRenderer.reset();
	}
}

void RenderManager::setTargetFBO(uint32_t fbo)
{
    this->targetFBO = fbo;
}

void RenderManager::unbindFrameBuffer()
{
    this->graphicsWrapper->unbindFrameBuffer();
}

} // namespace
