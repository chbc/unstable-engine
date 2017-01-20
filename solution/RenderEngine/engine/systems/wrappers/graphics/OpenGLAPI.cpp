#include <windows.h>
#include <GL/glew.h>

#include "OpenGLAPI.h"
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/utils/FileUtils.h>
#include <engine/utils/Log.h>

namespace sre
{

namespace EAttribLocation
{

enum Type : int
{
	POSITION = 0,
	NORMAL = 1,
	TEXCOORDS = 2
};

}

void OpenGLAPI::init()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw std::string("GLEW didn't inited");

	const GLubyte *glVersion = glGetString(GL_VERSION);
	std::string strGLVersion((char *)(glVersion));
	Log::logMessage("OpenGL Version: " + strGLVersion);

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
	int size = mesh->indices.size();
	uint32_t *indices = new uint32_t[size];
	for (int i = 0; i < size; i++)
		indices[i] = mesh->indices[i];

	// Creates IBO
	glGenBuffers(1, &mesh->indexBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);

	delete[] indices;
}

void OpenGLAPI::drawColorMesh(MeshComponent *mesh)
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

	this->enableVertexAndNormalLocation(EAttribLocation::POSITION, EAttribLocation::NORMAL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBO);
	glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, NULL);

	// Clear
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	this->disableVertexAndNormalLocation(EAttribLocation::POSITION, EAttribLocation::NORMAL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLAPI::drawTexturedMesh(MeshComponent *mesh, uint32_t textureId)
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

	this->enableVertexAndNormalLocation(EAttribLocation::POSITION, EAttribLocation::NORMAL);
	
	glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)(sizeof(glm::vec3) * 2));
	glEnableVertexAttribArray(EAttribLocation::TEXCOORDS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBO);
	glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, nullptr);

	// Clear
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	this->disableVertexAndNormalLocation(EAttribLocation::POSITION, EAttribLocation::NORMAL);
	glDisableVertexAttribArray(EAttribLocation::TEXCOORDS);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLAPI::clearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

uint32_t OpenGLAPI::setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void *data)
{
	uint32_t result = 0;

	glGenTextures(1, &result);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, result);

	int colorFormat = (bpp == 3) ? GL_RGB : GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	return result;
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
	this->checkProgramLink(program);

	return program;
}

void OpenGLAPI::setInt(uint32_t program, const std::string &varName, int value)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform1i(location, value);
}

void OpenGLAPI::setFloat(uint32_t program, const std::string &varName, float value)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform1f(location, value);
}

void OpenGLAPI::setVec3(uint32_t program, const std::string &varName, const float *value)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform3fv(location, 1, value);
}

void OpenGLAPI::setVec4(uint32_t program, const std::string &varName, const float *value)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniform4fv(location, 1, value);
}

void OpenGLAPI::setMat4(uint32_t program, const std::string &varName, const float *value)
{
	int location = glGetUniformLocation(program, varName.c_str());
	this->checkVariableLocation(location, varName);
	glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

/*
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
*/

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
void OpenGLAPI::enableVertexAndNormalLocation(int vertexLocation, int normalLocation)
{
	// Vertices
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)0);
	glEnableVertexAttribArray(vertexLocation);

	// Normals
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)sizeof(glm::vec3));
	glEnableVertexAttribArray(normalLocation);
}

void OpenGLAPI::disableVertexAndNormalLocation(int vertexLocation, int normalLocation)
{
	glDisableVertexAttribArray(vertexLocation);
	glDisableVertexAttribArray(normalLocation);
}

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

void OpenGLAPI::checkProgramLink(uint32_t program)
{
	int result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		char error[1000];
		glGetProgramInfoLog(program, 1000, NULL, error);

		glDeleteProgram(program);

		throw error;
	}
}
//

} // namespace
