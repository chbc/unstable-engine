#include <windows.h>
#include <GL/glew.h>
#include <SDL/SDL_opengl.h>

#include "OpenGLAPI.h"
#include <engine/nodes/renderables/meshes/Mesh.h>

#include <string>
#include <iostream>

namespace sre
{

void OpenGLAPI::init()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw std::string("GLEW didn't inited");

	const GLubyte *glVersion = glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << glVersion << std::endl;

	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void OpenGLAPI::createVBO(Mesh *mesh)
{
	// data
	int ttSize = mesh->vertexData->size();
	VertexData *vertexDataArray = new VertexData[ttSize];
	for (int i = 0; i < ttSize; i++)
		vertexDataArray[i] = mesh->vertexData->at(i);

	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertexData->size() * sizeof(VertexData), vertexDataArray, GL_STATIC_DRAW);
	delete[] vertexDataArray;
}

void OpenGLAPI::createIBO(Mesh *mesh)
{
	// indices
	int indCount = mesh->indices->size();
	unsigned int *indices = new unsigned int[indCount];
	for (int i = 0; i < indCount; i++)
		indices[i] = mesh->indices->at(i);



	//Create IBO
	glGenBuffers(1, &mesh->indexBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

	delete[] indices;
}

void OpenGLAPI::drawMesh(Mesh *mesh)
{
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
}

void OpenGLAPI::clearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLAPI::TEST_drawTriangle()
{
	GLfloat vertices[] =
	{
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		0.0f, 1.0f, -1.0f
	};
	GLubyte indices[] = { 0, 1, 2 };

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
}

} // namespace
