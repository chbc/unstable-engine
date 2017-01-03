#include "RenderManager.h"

#include <engine/entities/Entity.h>
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/entities/components/cameras/CameraComponent.h>
#include <engine/systems/wrappers/graphics/OpenGLAPI.h>
#include <engine/systems/multimedia/MultimediaManager.h>
#include "MatrixManager.h"
#include "ShaderManager.h"
#include "LightManager.h"
#include <engine/entities/components/meshes/materials/Material.h>
#include "renders/ColorRenderer.h"

namespace sre
{

IMPLEMENT_SINGLETON(RenderManager);

RenderManager::RenderManager()
{
	/* ###
	this->textureManager = TextureManager::getInstance();
	*/ 

	this->graphicsWrapper	= SPTR<AGraphicsWrapper>{ new OpenGLAPI{} };
	this->shaderManager		= UPTR<ShaderManager>{ new ShaderManager{this->graphicsWrapper} };
	this->matrixManager		= UPTR<MatrixManager>{ new MatrixManager{} };
	this->lightManager		= UPTR<LightManager>{ new LightManager{} };
	
	this->colorRenderer		= UPTR<ColorRenderer>{ nullptr };
	this->mainCamera		= UPTR<CameraComponent>{ nullptr };
}

void RenderManager::init()
{
	this->graphicsWrapper->init();

	const float FOV{45.0f};
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
	if (this->colorRenderer.get() == nullptr)
		this->colorRenderer = UPTR<ColorRenderer>{ new ColorRenderer{} };

	this->colorRenderer->addMesh(mesh);
}

void RenderManager::setMainCamera(CameraComponent *camera)
{
	this->mainCamera.reset(camera);
}
	
CameraComponent *RenderManager::getMainCamera()
{
	return this->mainCamera.get();
}

void RenderManager::render()
{
	this->renderCamera();
	this->colorRenderer->render(this->matrixManager.get(), this->shaderManager.get(), this->graphicsWrapper.get());
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

void RenderManager::createVBO(MeshComponent *mesh)
{
    unsigned int program = mesh->material->getShaderProgram();
    mesh->vertexAttribLocation = this->shaderManager->getAttribLocation(program, EShaderVariable::SHADER_POSITION);
    mesh->normalAttribLocation = this->shaderManager->getAttribLocation(program, EShaderVariable::SHADER_NORMAL);

	this->graphicsWrapper->createVBO(mesh);
	this->graphicsWrapper->createIBO(mesh);
}

DirectionalLightComponent *RenderManager::addDirectionalLight(Entity *entity)
{
    return this->lightManager->addDirectionalLight(entity);
}

PointLightComponent *RenderManager::addPointLight(Entity *entity)
{
    return this->lightManager->addPointLight(entity);
}

void RenderManager::DEBUG_drawTriangle()
{
	OpenGLAPI::DEBUG_drawTriangle();
}

void RenderManager::clearBuffer()
{
	this->graphicsWrapper->clearBuffer();
}

/* ###
void RenderManager::applyMaterial(Material *material, bool receiveLight)
{

}

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

/*
void RenderManager::releaseMaterial(Material *material)
{
    // ### TODO
}
*/

/* ###
Texture *RenderManager::loadTexture(const std::string &fileName)
{
	return this->textureManager->loadTexture(fileName);
}
*/

unsigned int RenderManager::loadShader(const std::string &vertFile, const std::string &fragFile)
{
	return this->shaderManager->loadShader(vertFile, fragFile);
}

void RenderManager::release()
{
	/* ###
	this->textureManager->release();
	delete this->textureManager;
	*/
}

} // namespace
