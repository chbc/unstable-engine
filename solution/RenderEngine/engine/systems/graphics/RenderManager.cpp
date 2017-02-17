#include "RenderManager.h"

#include <engine/entities/Entity.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/systems/wrappers/graphics/OpenGLAPI.h>
#include <engine/systems/multimedia/MultimediaManager.h>
#include "MatrixManager.h"
#include "LightManager.h"
#include "TextureManager.h"
#include <engine/entities/components/meshes/materials/Material.h>
#include "renders/ColorRenderer.h"
#include "renders/DiffuseTexturedRenderer.h"
#include "renders/NormalMapRenderer.h"
#include "renders/SpecularMapRenderer.h"
#include "renders/AOMapRenderer.h"

namespace sre
{

IMPLEMENT_SINGLETON(RenderManager);

RenderManager::RenderManager()
{
	this->graphicsWrapper	= SPTR<AGraphicsWrapper>{ new OpenGLAPI{} };
	this->matrixManager		= UPTR<MatrixManager>{ new MatrixManager{} };
	this->lightManager		= UPTR<LightManager>{ new LightManager{} };
	this->textureManager	= UPTR<TextureManager>{ new TextureManager{ this->graphicsWrapper.get() } };
	
	this->colorRenderer		= UPTR<ColorRenderer>{ nullptr };
	this->diffuseRenderer	= UPTR<ColorRenderer>{ nullptr };
	this->normalMapRenderer = UPTR<ColorRenderer>{ nullptr };
	this->specularMapRenderer = UPTR<ColorRenderer>{ nullptr };
	this->aoMapRenderer		= UPTR<ColorRenderer>{ nullptr };
	this->mainCamera		= nullptr;
}

void RenderManager::init()
{
	this->graphicsWrapper->init();

	const float FOV{90.0f};
	this->matrixManager->setProjection(FOV, MultimediaManager::SCREEN_WIDTH/MultimediaManager::SCREEN_HEIGHT, 0.1f, 100);
}

void RenderManager::addMesh(MeshComponent *mesh)
{
	ColorRenderer *renderer = this->chooseRenderer(mesh);
	renderer->createVBO(mesh);
	renderer->addMesh(mesh);
}

void RenderManager::onBeforeMaterialChange(MeshComponent *mesh)
{
	ColorRenderer *renderer = this->chooseRenderer(mesh);
	renderer->removeMesh(mesh);
}

void RenderManager::onAfterMaterialChange(MeshComponent *mesh)
{
	ColorRenderer *renderer = this->chooseRenderer(mesh);
	renderer->addMesh(mesh);
}

ColorRenderer *RenderManager::chooseRenderer(MeshComponent *mesh)
{
	ColorRenderer *result = nullptr;

	Material *material = mesh->getMaterial();
	if (material->hasComponent<AmbientOcclusionMaterialComponent>())
	{
		if (this->aoMapRenderer.get() == nullptr)
		{
			this->aoMapRenderer = UPTR<AOMapRenderer>{ new AOMapRenderer{this->graphicsWrapper} };
			this->aoMapRenderer->loadShader(); // ### tambem é chamado ao remover!
		}

		result = this->aoMapRenderer.get();
	}
	else if (material->hasComponent<SpecularMaterialComponent>())
	{
		if (this->specularMapRenderer.get() == nullptr)
		{
			this->specularMapRenderer = UPTR <SpecularMapRenderer>{ new SpecularMapRenderer{this->graphicsWrapper} };
			this->specularMapRenderer->loadShader();
		}

		result = this->specularMapRenderer.get();
	}
	else if (material->hasComponent<NormalMaterialComponent>())
	{
		if (this->normalMapRenderer.get() == nullptr)
		{
			this->normalMapRenderer = UPTR<NormalMapRenderer>{ new NormalMapRenderer{this->graphicsWrapper} };
			this->normalMapRenderer->loadShader();
		}

		result = this->normalMapRenderer.get();
	}
	else if (material->hasComponent<DiffuseMaterialComponent>())
	{
		if (this->diffuseRenderer.get() == nullptr)
		{
			this->diffuseRenderer = UPTR<DiffuseTexturedRenderer>{ new DiffuseTexturedRenderer{this->graphicsWrapper} };
			this->diffuseRenderer->loadShader();
		}

		result = this->diffuseRenderer.get();
	}
	else if (material->hasComponent<ColorMaterialComponent>())
	{
		if (this->colorRenderer.get() == nullptr)
		{
			this->colorRenderer = UPTR<ColorRenderer>{ new ColorRenderer{this->graphicsWrapper} };
			this->colorRenderer->loadShader();
		}

		result = this->colorRenderer.get();
	}

	return result;
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

	const int MAX_RENDERS = 5;
	ColorRenderer *renders[MAX_RENDERS]
	{
		this->colorRenderer.get(),
		this->diffuseRenderer.get(),
		this->normalMapRenderer.get(),
		this->specularMapRenderer.get(),
		this->aoMapRenderer.get()
	};

	for (ColorRenderer *item : renders)
	{
		if ((item != nullptr) && (item->hasMeshes()))
		{
			item->render
			(
				this->matrixManager.get(), 
				this->lightManager.get(), 
				this->mainCamera->getTransform()->getPosition()
			);
		}
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
