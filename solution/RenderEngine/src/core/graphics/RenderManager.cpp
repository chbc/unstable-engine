#include "RenderManager.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "GUITextComponent.h"
#include "CameraComponent.h"
#include "OpenGLAPI.h"
#include "OpenGLESAPI.h"
#include "TextureManager.h"
#include "SingletonsManager.h"
#include "MeshData.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "MeshRenderer.h"
#include "GUIRenderer.h"
#include "ShadowRenderer.h"
#include "PostProcessingRenderer.h"
#include "PostProcessingComponent.h"
#include "EngineValues.h"

#include "CollectionsUtils.h"

namespace sre
{

RenderManager::RenderManager()
{
    SingletonsManager *singletonsManager = SingletonsManager::getInstance();

#ifdef __ANDROID__
    this->graphicsWrapper   = singletonsManager->add<AGraphicsWrapper, OpenGLESAPI>();
#else
    this->graphicsWrapper = singletonsManager->add<AGraphicsWrapper, OpenGLAPI>();
#endif

    this->lightManager      = singletonsManager->resolve<LightManager>();
    this->shaderManager     = singletonsManager->resolve<ShaderManager>();

    this->mainCamera = nullptr;
    this->targetFBO = 0;
}

void RenderManager::init()
{
    this->graphicsWrapper->init();
    this->shaderManager->init();
    this->lightManager->init();

    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	
    singletonsManager->resolve<TextureManager>()->init();
}

void RenderManager::preRelease()
{
    this->opaqueMeshRenderers.clear();
    this->translucentMeshRenderers.clear();
    this->guiRenderer = nullptr;
}

void RenderManager::addEntity(Entity *entity)
{
    if (entity->hasComponent<MeshComponent>())
    {
        MeshComponent *mesh = entity->getComponent<MeshComponent>();
        this->addMesh(mesh);
    }
    else if (entity->hasComponent<GUIImageComponent>())
    {
        GUIImageComponent *guiComponent = entity->getComponent<GUIImageComponent>();
        this->addGUIComponent(guiComponent);
    }
    else if (entity->hasComponent<GUITextComponent>())
    {
        GUITextComponent *guiComponent = entity->getComponent<GUITextComponent>();
        this->addDynamicGUIComponent(guiComponent);
    }
    
    uint32_t size = entity->getChildrenCount();
    for (uint32_t i = 0; i < size; i++)
        this->addEntity(entity->getChild(i));
}

void RenderManager::addMesh(MeshComponent *mesh)
{
    if (mesh->isOpaque())
        this->addMesh(this->opaqueMeshRenderers, mesh);
    else
        this->addMesh(this->translucentMeshRenderers, mesh);

    if (mesh->getMaterial()->castShadow)
    {
        this->initShadowRenderer();
        this->shadowRenderer->addItem(mesh);
    }
}

void RenderManager::addMesh(VECTOR_UPTR<MeshRenderer>& renderers, MeshComponent* mesh)
{
    MeshRenderer* renderer = nullptr;
    for (const UPTR<MeshRenderer>& item : renderers)
    {
        if (item->fitsWithMesh(mesh))
        {
            renderer = item.get();
            break;
        }
    }

    if (renderer == nullptr)
    {
        renderer = new MeshRenderer{ mesh->getMaterial(), this->shaderManager, this->graphicsWrapper };
        renderers.emplace_back(renderer);
    }

    renderer->addMesh(mesh);
}

void RenderManager::addGUIComponent(GUIImageComponent *guiComponent)
{
    if (guiComponent->isAbleToBeRendered())
    {
        this->initGUIRenderer();
        this->guiRenderer->addGUIComponent(guiComponent);
    }
}

void RenderManager::addDynamicGUIComponent(GUIImageComponent *guiComponent)
{
    this->initGUIRenderer();
    this->guiRenderer->addDynamicGUIComponent(guiComponent);
}

void RenderManager::initGUIRenderer()
{
    if (this->guiRenderer.get() == nullptr)
    {
        this->guiRenderer = UPTR<GUIRenderer>{ new GUIRenderer{this->shaderManager, this->graphicsWrapper} };
        this->guiRenderer->loadShader();
    }
}

void RenderManager::initShadowRenderer()
{
    if (this->shadowRenderer.get() == nullptr)
    {
        this->shadowRenderer = UPTR<ShadowRenderer>{ new ShadowRenderer };
    }
}

void RenderManager::onSceneLoaded()
{
    if (this->mainCamera == nullptr)
        return;

    if (this->shadowRenderer.get() != nullptr)
        this->shadowRenderer->onSceneLoaded();

	bool useBrightnessSegmentation = false;
    bool includeDepth = false;
	Entity* cameraEntity = this->mainCamera->getEntity();
	if (cameraEntity->hasComponent<PostProcessingComponent>())
	{
		PostProcessingComponent* postProcessingComponent = cameraEntity->getComponent<PostProcessingComponent>();
		this->postProcessingRenderer = UPTR<PostProcessingRenderer>{ new PostProcessingRenderer };
		this->postProcessingRenderer->onSceneLoaded(postProcessingComponent);

		useBrightnessSegmentation = this->postProcessingRenderer->isUsingBrightnessSegmentation();
        includeDepth = this->postProcessingRenderer->isIncludingDepth();
	}

	for (const UPTR<MeshRenderer>& item : this->opaqueMeshRenderers)
		item->onSceneLoaded(useBrightnessSegmentation, includeDepth);

    for (const UPTR<MeshRenderer>& item : this->translucentMeshRenderers)
        item->onSceneLoaded(useBrightnessSegmentation, includeDepth);
}

void RenderManager::setMainCamera(CameraComponent *camera)
{
    this->mainCamera = camera;
}

CameraComponent *RenderManager::getMainCamera()
{
    return this->mainCamera;
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

    if (this->mainCamera != nullptr)
    {
        this->mainCamera->updateView();
        for (const UPTR<MeshRenderer>& item : this->opaqueMeshRenderers)
            item->render(this->mainCamera->getTransform()->getPosition());

        for (const UPTR<MeshRenderer>& item : this->translucentMeshRenderers)
            item->render(this->mainCamera->getTransform()->getPosition());
    }

	// Post processing rendering
	if (this->postProcessingRenderer.get() != nullptr)
		this->postProcessingRenderer->onPostRender(this->targetFBO);

    // GUI rendering
    if (this->guiRenderer.get() != nullptr)
        this->guiRenderer->render();

    this->graphicsWrapper->unbindFrameBuffer();
}

void RenderManager::DEBUG_drawTriangle()
{
#ifndef __ANDROID__
    OpenGLAPI::DEBUG_drawTriangle();
#endif
}

void RenderManager::setupBufferSubData(GUIMeshData* meshData)
{
    this->graphicsWrapper->bindVAO(meshData->vao, meshData->vbo);
    this->graphicsWrapper->setupBufferSubData(meshData);
}

void RenderManager::onRemoveDestroyedEntities()
{
    for (const UPTR<MeshRenderer> &item : this->opaqueMeshRenderers)
        item->onRemoveDestroyedEntities();

    for (const UPTR<MeshRenderer>& item : this->translucentMeshRenderers)
        item->onRemoveDestroyedEntities();

    CollectionsUtils::removeIfRendererIsEmpty(this->opaqueMeshRenderers);
    CollectionsUtils::removeIfRendererIsEmpty(this->translucentMeshRenderers);

    if (this->guiRenderer.get() != nullptr)
    {
        this->guiRenderer->removeDestroyedEntities();
        if (this->guiRenderer->isEmpty())
            this->guiRenderer = nullptr;
    }

    this->lightManager->removeDestroyedEntities();
}

DirectionalLightComponent* RenderManager::AddDirectionalLight(Entity* entity)
{
    return this->lightManager->addDirectionalLight(entity);
}

PointLightComponent* RenderManager::AddPointLight(Entity* entity)
{
    return this->lightManager->addPointLight(entity);
}

void RenderManager::setTargetFBO(uint32_t fbo)
{
    this->targetFBO = fbo;
}

} // namespace
