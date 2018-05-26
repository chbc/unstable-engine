#include "RenderManager.h"

#include <engine/entities/Entity.h>
#include <engine/entities/components/renderables/meshes/MeshComponent.h>
#include <engine/entities/components/renderables/gui/GUITextComponent.h>
#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/core/wrappers/graphics/OpenGLAPI.h>
#include <engine/core/multimedia/textures/TextureManager.h>
#include <engine/core/multimedia/MultimediaManager.h>
#include <engine/core/singletonsManager/SingletonsManager.h>
#include "meshData/MeshData.h"
#include "MatrixManager.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "renders/Renderer.h"
#include "renders/GUIRenderer.h"
#include <experimental/vector>

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
    this->guiRenderer = UPTR<GUIRenderer>{ nullptr };
}

void RenderManager::init()
{
    this->graphicsWrapper->init();
    this->shaderManager->init();
    this->textureManager->init();

    MultimediaManager *multimediaManager = SingletonsManager::getInstance()->resolve<MultimediaManager>();
    const float FOV{90.0f};
    this->matrixManager->setProjection(FOV, multimediaManager->getAspectRatio(), 0.1f, 100);
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
        renderer->loadShader();
        this->renders.emplace_back(renderer);
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

void RenderManager::onSceneLoaded()
{
    this->lightManager->onSceneLoaded();
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
    this->renderCamera();

    for (const UPTR<Renderer> &item : this->renders)
    {
        item->render
        (
            this->matrixManager,
            this->lightManager,
            this->mainCamera->getTransform()->getPosition()
        );
    }
    
    if (this->guiRenderer.get() != nullptr)
        this->guiRenderer->render(this->matrixManager);
}

void RenderManager::renderCamera()
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

void RenderManager::clearBuffer()
{
    this->graphicsWrapper->clearBuffer();
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

void RenderManager::setupBufferSubData(const GUIImageComponent *guiComponent)
{
    this->graphicsWrapper->bindVAO(guiComponent->vao, guiComponent->vbo);
    this->graphicsWrapper->setupBufferSubData(guiComponent->meshData.get());
}

void RenderManager::removeDestroyedEntities()
{
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
}

} // namespace
