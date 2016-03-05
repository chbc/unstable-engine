#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>

#include <iostream>

#include "RenderManager.h"
#include <engine/systems/multimedia/MultimediaManager.h>
#include <engine/nodes/renderables/RenderableNode.h>
#include <engine/nodes/renderables/materials/DiffuseMaterial.h>

namespace sre
{

IMPLEMENT_SINGLETON(RenderManager);

RenderManager::RenderManager()
{
	this->textureManager = TextureManager::getInstance();
	this->shaderManager	 = ShaderManager::getInstance();
	this->lightManager	 = LightManager::getInstance();
	this->matrixManager = new MatrixManager;
	this->graphicsWrapper = AGraphicsWrapper::getInstance();
}

bool RenderManager::init()
{
	this->graphicsWrapper->init();

	const float FOV{45.0f};
	this->matrixManager->setProjection(FOV, MultimediaManager::WIDTH/MultimediaManager::HEIGHT, 1, 100);

	if (!this->textureManager->init())
	{
		std::cout << "TextureManager error: init" << std::endl;
		return false;
	}

	if (!this->shaderManager->init())
	{
		std::cout << "ShaderManager error: init" << std::endl;
		return false;
	}

	if (!this->lightManager->init())
	{
		std::cout << "LightManager error: init" << std::endl;
		return false;
	}

	return true;
}

void RenderManager::release()
{
	this->textureManager->release();
	delete this->textureManager;

	this->shaderManager->release();
	delete this->shaderManager;

	this->lightManager->release();
	delete this->lightManager;

	delete this->matrixManager;
}

void RenderManager::createBufferObject(Mesh *mesh)
{
    unsigned int program = mesh->material->getShaderProgram();
    mesh->vertexAttribLocation = this->shaderManager->getAttribLocation(program, SHADER_POSITION);
    mesh->normalAttribLocation = this->shaderManager->getAttribLocation(program, SHADER_NORMAL);

	this->graphicsWrapper->createVBO(mesh);
	this->graphicsWrapper->createIBO(mesh);
}

DirectionalLight *RenderManager::addDirectionalLight()
{
    return this->lightManager->addDirectionalLight();
}

PointLight *RenderManager::addPointLight()
{
    return this->lightManager->addPointLight();
}

void RenderManager::render(const std::vector<RenderableNode *> &renderableNodes)
{
    // TODO: render children

    RenderableNode *item = NULL;
	int size = renderableNodes.size();

	for (int i = 0; i < size; i++)
	{
	    item = renderableNodes[i];

        this->matrixManager->push(item->getTransform()->getMatrix());
        this->matrixManager->update();

        for (unsigned int m = 0; m < item->meshes.size(); m++)
        {
            Mesh *mesh = item->meshes[m];
            mesh->applyMaterial(item->receiveLight);

            this->drawMesh(mesh);
        }

        this->matrixManager->pop();
	}
}

void RenderManager::DEBUG_drawTriangle()
{
	AGraphicsWrapper::DEBUG_drawTriangle();
}

void RenderManager::clearBuffer()
{
	this->graphicsWrapper->clearBuffer();
}

void RenderManager::applyMaterial(Material *material, bool receiveLight)
{
	unsigned int shaderProgram = material->getShaderProgram();
	this->shaderManager->enableShader(shaderProgram);

	glm::mat4 mvp = this->matrixManager->getMVP();
	this->shaderManager->setValue(shaderProgram, "MVP", &mvp[0][0]);

	if (receiveLight)
        this->lightManager->setupLights(shaderProgram);
}

void RenderManager::applyMaterial(DiffuseMaterial *material, std::vector<VertexData> *vertexData, bool receiveLight)
{
    this->applyMaterial(material, receiveLight);

	// texture //
	// TODO: acertar texCoords
	/*
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, material->getTextureID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	*/
}

void RenderManager::drawMesh(Mesh *mesh)
{
	this->graphicsWrapper->drawMesh(mesh);
	this->shaderManager->disableShader();
}

void RenderManager::releaseMaterial(Material *material)
{
    // TODO
}

void RenderManager::renderCamera(Vector position, Vector lookTarget, Vector up)
{
    this->matrixManager->setView(position, lookTarget, up);
}

Texture *RenderManager::loadTexture(const std::string &fileName)
{
	return this->textureManager->loadTexture(fileName);
}

unsigned int RenderManager::loadShader(const std::string &vertFile, const std::string &fragFile)
{
	return this->shaderManager->loadShader(vertFile, fragFile);
}

} // namespace
