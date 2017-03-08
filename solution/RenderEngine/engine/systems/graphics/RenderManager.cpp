#include "RenderManager.h"

#include <engine/entities/Entity.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/systems/wrappers/graphics/OpenGLAPI.h>
#include <engine/systems/multimedia/MultimediaManager.h>
#include "MatrixManager.h"
#include "LightManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "renders/Renderer.h"

namespace sre
{

IMPLEMENT_SINGLETON(RenderManager)

RenderManager::RenderManager()
{
	this->graphicsWrapper	= SPTR<AGraphicsWrapper>{ new OpenGLAPI{} };
	this->matrixManager		= UPTR<MatrixManager>{ new MatrixManager{} };
	this->lightManager		= UPTR<LightManager>{ new LightManager{} };
	this->textureManager	= UPTR<TextureManager>{ new TextureManager{ this->graphicsWrapper.get() } };
	this->shaderManager		= SPTR<ShaderManager>{ new ShaderManager{this->graphicsWrapper} };
	this->mainCamera		= nullptr;
}

void RenderManager::init()
{
	this->graphicsWrapper->init();

	const float FOV{90.0f};
	this->matrixManager->setProjection(FOV, MultimediaManager::SCREEN_WIDTH/MultimediaManager::SCREEN_HEIGHT, 0.1f, 100);
}

void RenderManager::addEntityMeshes(Entity *entity)
{
	if (entity->hasComponent<MeshComponent>())
	{
		MeshComponent *mesh = entity->getComponent<MeshComponent>();
		this->addMesh(mesh);
	}

	uint32_t size = entity->getChildrenCount();
	for (uint32_t i = 0; i < size; i++)
		this->addEntityMeshes(entity->getChild(i));
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
			this->matrixManager.get(), 
			this->lightManager.get(), 
			this->mainCamera->getTransform()->getPosition()
		);
	}
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

void RenderManager::release()
{
}

} // namespace
