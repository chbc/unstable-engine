#include "RenderManager.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "GUITextComponent.h"
#include "CameraComponent.h"
#include "OpenGLAPI.h"
#include "OpenGLESAPI.h"
#include "TextureManager.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"
#include "MeshData.h"
#include "MatrixManager.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "Renderer.h"
#include "GUIRenderer.h"
#include "ShadowRenderer.h"
#include "PostProcessingRenderer.h"

namespace sre
{

RenderManager::RenderManager()
{
    SingletonsManager *singletonsManager = SingletonsManager::getInstance();
    this->graphicsWrapper   = singletonsManager->add<AGraphicsWrapper, OpenGLAPI>();
    this->matrixManager     = singletonsManager->resolve<MatrixManager>();
    this->lightManager      = singletonsManager->resolve<LightManager>();
    this->textureManager    = singletonsManager->resolve<TextureManager>();
    this->shaderManager     = singletonsManager->resolve<ShaderManager>();

    this->mainCamera = nullptr;
}

void RenderManager::init()
{
    this->graphicsWrapper->init();
    this->shaderManager->init();
    this->textureManager->init();
    this->lightManager->init();

    MultimediaManager *multimediaManager = SingletonsManager::getInstance()->resolve<MultimediaManager>();
    const float FOV{120.0f};
    this->matrixManager->setProjection(FOV, multimediaManager->getAspectRatio(), 0.1f, 1000);
	this->screenWidth = multimediaManager->getScreenWidth();
	this->screenHeight = multimediaManager->getScreenHeight();

	this->initPostProcessingRenderer();
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
    Renderer *renderer = nullptr;
    for (const UPTR<Renderer> &item : this->renders)
    {
        if (item->fitsWithMesh(mesh))
        {
            renderer = item.get();
            break;
        }
    }

    if (renderer == nullptr)
    {
        renderer = new Renderer{mesh->getMaterial(), this->shaderManager, this->graphicsWrapper};
        this->renders.emplace_back(renderer);
    }
    
    renderer->addMesh(mesh);

    if (mesh->getMaterial()->castsShadow)
    {
        this->initShadowRenderer();
        this->shadowRenderer->addItem(mesh);
    }
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

void RenderManager::initPostProcessingRenderer()
{
	if (this->postProcessingRenderer.get() == nullptr)
	{
		this->postProcessingRenderer = UPTR<PostProcessingRenderer>{ new PostProcessingRenderer };
	}
}

void RenderManager::onSceneLoaded()
{
    if (this->shadowRenderer.get() != nullptr)
        this->shadowRenderer->onSceneLoaded();

    for (const UPTR<Renderer> &item : this->renders)
        item->onSceneLoaded();
	
	if (this->postProcessingRenderer.get() != nullptr)
		this->postProcessingRenderer->onSceneLoaded();
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
	if (this->postProcessingRenderer.get() != nullptr)
		this->postProcessingRenderer->bindFrameBuffer();

    this->graphicsWrapper->setViewport(this->screenWidth, this->screenHeight);
    this->graphicsWrapper->clearColorAndDepthBuffer();

    this->updateViewMatrix();
    for (const UPTR<Renderer> &item : this->renders)
    {
        item->render
        (
            this->matrixManager,
            this->mainCamera->getTransform()->getPosition()
        );
    }

	// Post processing rendering
	if (this->postProcessingRenderer.get() != nullptr)
		this->postProcessingRenderer->render();

    // GUI rendering
    if (this->guiRenderer.get() != nullptr)
        this->guiRenderer->render(this->matrixManager);
}

void RenderManager::updateViewMatrix()
{
    this->matrixManager->setView
    (
        this->mainCamera->getTransform()->getPosition(),
        this->mainCamera->lookAtTarget,
        this->mainCamera->up
    );
}

void RenderManager::DEBUG_drawTriangle()
{
    OpenGLAPI::DEBUG_drawTriangle();
}

DirectionalLightComponent *RenderManager::addDirectionalLight(Entity *entity)
{
    return this->lightManager->addDirectionalLight(entity);
}

PointLightComponent *RenderManager::addPointLight(Entity *entity)
{
    return this->lightManager->addPointLight(entity);
}

Texture *RenderManager::loadGUITexture(const std::string &fileName)
{
    return this->textureManager->loadGUITexture(fileName);
}

Texture *RenderManager::loadDiffuseTexture(const std::string &fileName)
{
    return this->textureManager->loadDiffuseTexture(fileName);
}

Texture *RenderManager::loadNormalTexture(const std::string &fileName)
{
    return this->textureManager->loadNormalTexture(fileName);
}

Texture *RenderManager::loadSpecularTexture(const std::string &fileName)
{
    return this->textureManager->loadSpecularTexture(fileName);
}

Texture *RenderManager::loadAOTexture(const std::string &fileName)
{
    return this->textureManager->loadAOTexture(fileName);
}

void RenderManager::setupBufferSubData(GUIMeshData* meshData)
{
    this->graphicsWrapper->bindVAO(meshData->vao, meshData->vbo);
    this->graphicsWrapper->setupBufferSubData(meshData);
}

void RenderManager::removeDestroyedEntities()
{
	/* ###
    for (const UPTR<Renderer> &item : this->renders)
        item->removeDestroyedEntities();

    std::experimental::erase_if
    (
        this->renders, 
        [](const UPTR<Renderer> &item) { return item->isEmpty(); }
    );

    if (this->guiRenderer.get() != nullptr)
        this->guiRenderer->removeDestroyedEntities();

    this->lightManager->removeDestroyedEntities();
	*/
}

} // namespace
