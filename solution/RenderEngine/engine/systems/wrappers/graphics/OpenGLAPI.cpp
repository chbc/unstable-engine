#include <windows.h>
#include <GL/glew.h>

#include "OpenGLAPI.h"
#include <engine/entities/renderables/meshes/Mesh.h>
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

void OpenGLAPI::deleteTexture(unsigned int id)
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
unsigned int OpenGLAPI::loadVertexShader(const std::string &vertexFile)
{
	return this->loadShader(vertexFile, GL_VERTEX_SHADER);
}

unsigned int OpenGLAPI::loadFragmentShader(const std::string &fragmentFile)
{
	return this->loadShader(fragmentFile, GL_FRAGMENT_SHADER);
}

unsigned int OpenGLAPI::createProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	return program;
}

void OpenGLAPI::setValue(unsigned int program, const std::string &varName, float x)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform1f(location, x);
}

void OpenGLAPI::setValue(unsigned int program, const std::string &varName, float x, float y)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform2f(location, x, y);
}

void OpenGLAPI::setValue(unsigned int program, const std::string &varName, float x, float y, float z)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform3f(location, x, y, z);
}

void OpenGLAPI::setValue(unsigned int program, const std::string &varName, float *matrix)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void OpenGLAPI::setValue(unsigned int program, const std::string &varName, int value)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform1i(location, value);
}

int OpenGLAPI::getAttribLocation(unsigned int program, EShaderVariable shaderVariable)
{
	int result = -1;
	std::string variable = "INVALID";

	switch (shaderVariable)
	{
		case SHADER_POSITION:   variable = "vertexPosition"; break;
		case SHADER_NORMAL:     variable = "inputNormal"; break;
		default: break;
	}

	result = glGetAttribLocation(program, variable.c_str());
	this->checkVariableLocation(result, variable);

	return result;
}

void OpenGLAPI::enableShader(unsigned int program)
{
	glUseProgram(program);
}

void OpenGLAPI::disableShader()
{
	glUseProgram(0);
}

void OpenGLAPI::releaseShaders(std::stack<unsigned int> &vertShaders, std::stack<unsigned int> &fragShaders, std::stack<unsigned int> &programs)
{
	unsigned int program = 0;
	unsigned int vertShader = 0;
	unsigned int fragShader = 0;

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
unsigned int OpenGLAPI::loadShader(const std::string &fileName, int shaderType)
{
	unsigned int result = 0;
	std::string source;
	FileUtils::loadFile(fileName, source);
	result = this->compileShader(fileName, source, shaderType);
	return result;
}

unsigned int OpenGLAPI::compileShader(const std::string &fileName, const std::string &source, unsigned int mode)
{
	unsigned int id = glCreateShader(mode);
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
