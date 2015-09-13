#include <windows.h>
#include <GL/glew.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

#include <iostream>

#include "RenderManager.h"
#include <engine/systems/multimedia/MultimediaManager.h>
#include <engine/nodes/renderables/RenderableNode.h>
#include <engine/nodes/renderables/materials/DiffuseMaterial.h>

namespace graphics
{

IMPLEMENT_SINGLETON(RenderManager);

RenderManager::RenderManager()
{
	this->textureManager = TextureManager::getInstance();
	this->shaderManager	 = ShaderManager::getInstance();
	this->lightManager	 = LightManager::getInstance();
}

bool RenderManager::init()
{
	using multimedia::MultimediaManager;

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return false;

	const GLubyte *glVersion = glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << glVersion << std::endl;
	delete glVersion;

	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	const float FOV = 80.0f;
	gluPerspective(FOV, MultimediaManager::WIDTH/MultimediaManager::HEIGHT, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);

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
}

void RenderManager::createBufferObject(Mesh *mesh)
{
    unsigned int program = mesh->material->getShaderProgram();
    mesh->vertexAttribLocation = this->shaderManager->getAttribLocation(program, SHADER_POSITION);
    mesh->normalAttribLocation = this->shaderManager->getAttribLocation(program, SHADER_NORMAL);

    // indices
    int indCount = mesh->indices->size();
    GLuint *indices = new GLuint[indCount];
    for (int i = 0; i < indCount; i++)
        indices[i] = mesh->indices->at(i);

    // data
    int ttSize = mesh->vertexData->size();
    VertexData *vertexDataArray = new VertexData[ttSize];
    for (int i = 0; i < ttSize; i++)
        vertexDataArray[i] = mesh->vertexData->at(i);


    glGenBuffers(1, &mesh->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertexData->size() * sizeof(VertexData), vertexDataArray, GL_STATIC_DRAW);

    //Create IBO
    glGenBuffers(1, &mesh->indexBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

    /*
	delete [] normals;
	delete [] vertices;
	*/
	delete [] indices;
	delete [] vertexDataArray;
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
    RenderableNode *item = NULL;
	int size = renderableNodes.size();

	for (int i = 0; i < size; i++)
	{
	    item = renderableNodes[i];

        this->pushTransform(item->getTransform());

        for (unsigned int m = 0; m < item->meshes.size(); m++)
        {
            Mesh *mesh = item->meshes[m];
            mesh->applyMaterial(item->receiveLight);
            this->drawMesh(mesh);
        }

        this->popTransform();
	}
}

void RenderManager::TEST_drawTriangle()
{
    GLfloat vertices[] =
    {
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        0.0f, 1.0f, -1.0f
    };
	GLubyte indices[] = {0, 1, 2};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void RenderManager::clearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderManager::applyMaterial(Material *material, bool receiveLight)
{
	unsigned int shaderProgram = material->getShaderProgram();
	this->shaderManager->enableShader(shaderProgram);

	if (receiveLight)
        this->lightManager->setupLights(shaderProgram);
}

void RenderManager::applyMaterial(DiffuseMaterial *material, std::vector<VertexData> *vertexData, bool receiveLight)
{
    this->applyMaterial(material, receiveLight);

	// texture //
	/* TODO: acertar texCoords
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, material->getTextureID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	*/
}

void RenderManager::drawMesh(Mesh *mesh)
{
/*
struct VertexData
{
    Vector position;
    Vector normal;
    Vector color;
    float u, v;
};
*/
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

    int vertexLocation = mesh->vertexAttribLocation;
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)0);
    glEnableVertexAttribArray(vertexLocation);

    int normalLocation = mesh->normalAttribLocation;
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)sizeof(Vector));
    glEnableVertexAttribArray(normalLocation);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBO);
    glDrawElements(GL_TRIANGLES, mesh->indices->size(), GL_UNSIGNED_INT, 0);

    // Clear
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(vertexLocation);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->shaderManager->disableShader();
}

void RenderManager::releaseMaterial(Material *material)
{

}

void RenderManager::pushTransform(Transform *transform)
{
	glPushMatrix();

	float *matrix = transform->getMatrix();
	glMultMatrixf(matrix);
}

void RenderManager::popTransform()
{
	glPopMatrix();
}

void RenderManager::renderCamera(Vector position, Vector lookTarget, Vector up)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(	position.x, position.y, position.z,
				lookTarget.x, lookTarget.y, lookTarget.z,
				up.x, up.y, up.z
			  );
}

Texture *RenderManager::loadTexture(const std::string &fileName)
{
	return this->textureManager->loadTexture(fileName);
}

unsigned int RenderManager::loadShader(const std::string &vertFile, const std::string &fragFile)
{
	return this->shaderManager->loadShader(vertFile, fragFile);
}

} // namespace graphics
