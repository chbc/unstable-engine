#include <windows.h>
#include <GL/glew.h>

#include "OpenGLAPI.h"
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/utils/FileUtils.h>

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

void OpenGLAPI::createVBO(MeshComponent *mesh)
{
	// data
	int ttSize = mesh->vertexData.size();
	VertexData *vertexDataArray = new VertexData[ttSize];
	for (int i = 0; i < ttSize; i++)
		vertexDataArray[i] = *mesh->vertexData[i].get();	// ###

	// Creates VBO
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertexData.size() * sizeof(VertexData), vertexDataArray, GL_STATIC_DRAW);
	delete[] vertexDataArray;
}

void OpenGLAPI::createIBO(MeshComponent *mesh)
{
	// indices
	int indCount = mesh->indices.size();
	uint32_t *indices = new uint32_t[indCount];
	for (int i = 0; i < indCount; i++)
		indices[i] = *mesh->indices[i].get();

	// Creates IBO
	glGenBuffers(1, &mesh->indexBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

	delete[] indices;
}

void OpenGLAPI::drawMesh(MeshComponent *mesh)
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

	int vertexLocation = mesh->vertexAttribLocation;
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)0);
	glEnableVertexAttribArray(vertexLocation);

	int normalLocation = mesh->normalAttribLocation;
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)sizeof(Vector));
	glEnableVertexAttribArray(normalLocation);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBO);
	glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);

	// Clear
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(vertexLocation);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLAPI::clearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLAPI::deleteTexture(uint32_t id)
{
	glDeleteTextures(1, &id);
}

void OpenGLAPI::DEBUG_drawTriangle()
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

// Shaders
uint32_t OpenGLAPI::loadVertexShader(const std::string &vertexFile)
{
	return this->loadShader(vertexFile, GL_VERTEX_SHADER);
}

uint32_t OpenGLAPI::loadFragmentShader(const std::string &fragmentFile)
{
	return this->loadShader(fragmentFile, GL_FRAGMENT_SHADER);
}

uint32_t OpenGLAPI::createProgram(uint32_t vertexShader, uint32_t fragmentShader)
{
	uint32_t program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	return program;
}

void OpenGLAPI::setValue(uint32_t program, const std::string &varName, float x)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform1f(location, x);
}

void OpenGLAPI::setValue(uint32_t program, const std::string &varName, float x, float y)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform2f(location, x, y);
}

void OpenGLAPI::setValue(uint32_t program, const std::string &varName, float x, float y, float z)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform3f(location, x, y, z);
}

void OpenGLAPI::setValue(uint32_t program, const std::string &varName, float *matrix)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void OpenGLAPI::setValue(uint32_t program, const std::string &varName, int value)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform1i(location, value);
}

int OpenGLAPI::getAttribLocation(uint32_t program, EShaderVariable::Type shaderVariable)
{
	int result = -1;
	std::string variable = "INVALID";

	switch (shaderVariable)
	{
		case EShaderVariable::SHADER_POSITION:   variable = "vertexPosition"; break;
		case EShaderVariable::SHADER_NORMAL:     variable = "inputNormal"; break;
		default: break;
	}

	result = glGetAttribLocation(program, variable.c_str());
	this->checkVariableLocation(result, variable);

	return result;
}

void OpenGLAPI::enableShader(uint32_t program)
{
	glUseProgram(program);
}

void OpenGLAPI::disableShader()
{
	glUseProgram(0);
}

void OpenGLAPI::releaseShaders(std::stack<uint32_t> &vertShaders, std::stack<uint32_t> &fragShaders, std::stack<uint32_t> &programs)
{
	uint32_t program = 0;
	uint32_t vertShader = 0;
	uint32_t fragShader = 0;

	while (!programs.empty())
	{
		program = programs.top();
		vertShader = vertShaders.top();
		fragShader = fragShaders.top();

		glDetachShader(program, vertShader);
		glDetachShader(program, fragShader);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		glDeleteProgram(program);

		programs.pop();
		vertShaders.pop();
		fragShaders.pop();
	}
}

// Private methods
uint32_t OpenGLAPI::loadShader(const std::string &fileName, int shaderType)
{
	uint32_t result = 0;
	std::string source;
	FileUtils::loadFile(fileName, source);
	result = this->compileShader(fileName, source, shaderType);
	return result;
}

uint32_t OpenGLAPI::compileShader(const std::string &fileName, const std::string &source, uint32_t mode)
{
	uint32_t id = glCreateShader(mode);
	const char *csource = source.c_str();

	glShaderSource(id, 1, &csource, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		char error[1000];
		glGetShaderInfoLog(id, 1000, NULL, error);

		throw "[OpenGLAPI] - In file: " + fileName + "\n" + error;
	}

	return id;
}

void OpenGLAPI::checkVariableLocation(int location, const std::string &varName)
{
	if (location == -1)
		throw ("[OpenGLAPI] Invalid shader variable: " + varName);
}
//

} // namespace
