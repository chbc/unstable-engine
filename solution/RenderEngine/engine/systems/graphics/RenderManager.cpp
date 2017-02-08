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

namespace sre
{

IMPLEMENT_SINGLETON(RenderManager);

RenderManager::RenderManager()
{
	/* ###
	this->textureManager = TextureManager::getInstance();
	*/ 

	this->graphicsWrapper	= SPTR<AGraphicsWrapper>{ new OpenGLAPI{} };
	this->matrixManager		= UPTR<MatrixManager>{ new MatrixManager{} };
	this->lightManager		= UPTR<LightManager>{ new LightManager{} };
	this->textureManager	= UPTR<TextureManager>{ new TextureManager{ this->graphicsWrapper.get() } };
	
	this->colorRenderer		= UPTR<ColorRenderer>{ nullptr };
	this->diffuseRenderer	= UPTR<DiffuseTexturedRenderer>{ nullptr };
	this->mainCamera		= nullptr;
}

void RenderManager::init()
{
	this->graphicsWrapper->init();

	const float FOV{90.0f};
	this->matrixManager->setProjection(FOV, MultimediaManager::SCREEN_WIDTH/MultimediaManager::SCREEN_HEIGHT, 1, 100);

	/*
	if (!this->textureManager->init())
	{
		std::cout << "TextureManager error: init" << std::endl;
		return false;
	}
	*/

}

void RenderManager::addMesh(MeshComponent *mesh)
{
	ColorRenderer *renderer = this->chooseRenderer(mesh);
	renderer->createVBO(mesh);
}

void RenderManager::onMaterialChange(MeshComponent *mesh)
{
	this->colorRenderer->removeMesh(mesh);
	this->chooseRenderer(mesh);
}

ColorRenderer *RenderManager::chooseRenderer(MeshComponent *mesh)
{
	ColorRenderer *result = nullptr;

	Material *material = mesh->getMaterial();
	if (material->hasComponent<DiffuseMaterialComponent>())
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

	result->addMesh(mesh);
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

	// Color renderer
	if (this->colorRenderer.get() != nullptr)
	{
		this->colorRenderer->render
		(
			this->matrixManager.get(), 
			this->lightManager.get(), 
			this->mainCamera->getTransform()->getPosition()
		);
	}

	// Diffuse renderer
	if (this->diffuseRenderer.get() != nullptr)
	{
		this->diffuseRenderer->render
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

/* ###
void RenderManager::applyMaterial(DiffuseMaterial *material, std::vector<VertexData> *vertexData, bool receiveLight)
{
    this->applyMaterial(material, receiveLight);

	// texture //
	// TODO: acertar texCoords
	 /* ###
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, material->getTextureID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	 // /
}
*/

Texture *RenderManager::loadTexture(const std::string &fileName)
{
	return this->textureManager->loadTexture(fileName);
}

void RenderManager::release()
{
	/* ###
	this->textureManager->release();
	delete this->textureManager;
	*/
}

} // namespace
