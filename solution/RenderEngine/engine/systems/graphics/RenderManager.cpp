#include "RenderManager.h"

#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/systems/wrappers/graphics/OpenGLAPI.h>
#include <engine/systems/multimedia/MultimediaManager.h>
#include "MatrixManager.h"
#include "ShaderManager.h"

/* ###
#include <engine/entities/renderables/RenderableNode.h>
#include <engine/entities/renderables/materials/DiffuseMaterial.h>
*/

namespace sre
{

IMPLEMENT_SINGLETON(RenderManager);

RenderManager::RenderManager()
{
	/* ###
	this->textureManager = TextureManager::getInstance();
	this->lightManager	 = LightManager::getInstance();
	*/ 

	this->graphicsWrapper	= SPTR<AGraphicsWrapper>{ new OpenGLAPI{} };
	//this->shaderManager		= UPTR<ShaderManager>{ new ShaderManager{this->graphicsWrapper} };
	//this->matrixManager		= UPTR<MatrixManager>{ new MatrixManager{} };
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



	if (!this->lightManager->init())
	{
		std::cout << "LightManager error: init" << std::endl;
		return false;
	}
	*/

}

void RenderManager::release()
{
	/* ###
	this->textureManager->release();
	delete this->textureManager;
	
	this->lightManager->release();
	delete this->lightManager;

	*/
}

void RenderManager::createBufferObject(MeshComponent *mesh)
{
	/*
    unsigned int program = mesh->material->getShaderProgram();
    mesh->vertexAttribLocation = this->shaderManager->getAttribLocation(program, EShaderVariable::SHADER_POSITION);
    mesh->normalAttribLocation = this->shaderManager->getAttribLocation(program, EShaderVariable::SHADER_NORMAL);

	this->graphicsWrapper->createVBO(mesh);
	this->graphicsWrapper->createIBO(mesh);
	*/
}

/* ###
DirectionalLight *RenderManager::addDirectionalLight()
{
    return this->lightManager->addDirectionalLight();
}

PointLight *RenderManager::addPointLight()
{
    return this->lightManager->addPointLight();
}
*/

/* ###
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
*/

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
	 /* ###
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, material->getTextureID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	 // /
}
*/

void RenderManager::drawMesh(MeshComponent *mesh)
{
	this->graphicsWrapper->drawMesh(mesh);
	this->shaderManager->disableShader();
}

/*
void RenderManager::releaseMaterial(Material *material)
{
    // TODO
}
*/

void RenderManager::renderCamera(const glm::vec3 &position, const glm::vec3 &lookTarget, const glm::vec3 &up)
{
    this->matrixManager->setView(position, lookTarget, up);
}

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

} // namespace
