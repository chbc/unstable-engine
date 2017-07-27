#include <windows.h>
#include <GL/glew.h>

#include "OpenGLAPI.h"
#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/entities/components/gui/GUIImageComponent.h>
#include <engine/utils/Log.h>

namespace sre
{

namespace EAttribLocation
{

enum Type : int
{
	POSITION = 0,
	NORMAL = 1,
	TEXCOORDS = 2,
	TANGENT = 3,
	BITANGENT = 4
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

void OpenGLAPI::createVAO(MeshComponent *mesh)
{
	// data
	int ttSize = mesh->vertexData.size();
	VertexData *vertexDataArray = new VertexData[ttSize];
	for (int i = 0; i < ttSize; i++)
		vertexDataArray[i] = *mesh->vertexData[i].get();	// ###

	// VAO
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	// VBO
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertexData.size() * sizeof(VertexData), vertexDataArray, GL_STATIC_DRAW);
	delete[] vertexDataArray;
}

void OpenGLAPI::createEBO(MeshComponent *mesh)
{
	// EBO
	glGenBuffers(1, &mesh->ebo);
	int size = mesh->indices.size();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), &mesh->indices[0], GL_STATIC_DRAW);
}

void OpenGLAPI::createGUIVAO(GUIImageComponent *guiComponent)
{
	// data
	int dataSize = guiComponent->vertexData.size();
	GUIVertexData *vertexDataArray = new GUIVertexData[dataSize];
	for (int i = 0; i < dataSize; i++)
		vertexDataArray[i] = *guiComponent->vertexData[i].get();

	// VAO
	glGenVertexArrays(1, &guiComponent->vao);
	glBindVertexArray(guiComponent->vao);

	// VBO
	glGenBuffers(1, &guiComponent->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, guiComponent->vbo);
	glBufferData(GL_ARRAY_BUFFER, guiComponent->vertexData.size() * sizeof(GUIVertexData), vertexDataArray, GL_STATIC_DRAW);
	delete[] vertexDataArray;
}

void OpenGLAPI::createGUIEBO(GUIImageComponent *guiComponent)
{
	// EBO
	glGenBuffers(1, &guiComponent->ebo);
	int size = guiComponent->indices.size();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, guiComponent->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), &guiComponent->indices[0], GL_STATIC_DRAW);
}

void OpenGLAPI::bindVAO(uint32_t vao, uint32_t vbo)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void OpenGLAPI::enableGUISettings()
{
	glEnableVertexAttribArray(EAttribLocation::POSITION);
	glVertexAttribPointer(EAttribLocation::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertexData), (GLvoid *)0);
	glEnableVertexAttribArray(EAttribLocation::TEXCOORDS);
	glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertexData), (GLvoid *)sizeof(glm::vec2));
}

void OpenGLAPI::enableVertexPositions()
{
	glEnableVertexAttribArray(EAttribLocation::POSITION);
	glVertexAttribPointer(EAttribLocation::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)0);
}

void OpenGLAPI::enableVertexNormals()
{
	glEnableVertexAttribArray(EAttribLocation::NORMAL);
	glVertexAttribPointer(EAttribLocation::NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)sizeof(glm::vec3));
}

void OpenGLAPI::enableTexCoords()
{
	glEnableVertexAttribArray(EAttribLocation::TEXCOORDS);
	glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)(sizeof(glm::vec3) * 2));
}

void OpenGLAPI::enableVertexTangents()
{
	int offset = (sizeof(glm::vec3) * 2) + (sizeof(float) * 2);
	glEnableVertexAttribArray(EAttribLocation::TANGENT);
	glVertexAttribPointer(EAttribLocation::TANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)offset);
}

void OpenGLAPI::enableVertexBitangents()
{
	int offset = (sizeof(glm::vec3) * 3) + (sizeof(float) * 2);
	glEnableVertexAttribArray(EAttribLocation::BITANGENT);
	glVertexAttribPointer(EAttribLocation::BITANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLvoid *)offset);
}

void OpenGLAPI::activeDiffuseTexture(uint32_t textureId)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void OpenGLAPI::activeNormalTexture(uint32_t textureId)
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void OpenGLAPI::activeSpecularTexture(uint32_t textureId)
{
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void OpenGLAPI::activeAOTexture(uint32_t textureId)
{
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void OpenGLAPI::drawElement(uint32_t vao, uint32_t indicesSize)
{
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void OpenGLAPI::disableVertexPositions()
{
	glDisableVertexAttribArray(EAttribLocation::POSITION);
}

void OpenGLAPI::disableVertexNormals()
{
	glDisableVertexAttribArray(EAttribLocation::NORMAL);
}

void OpenGLAPI::disableTexCoords()
{
	glDisableVertexAttribArray(EAttribLocation::TEXCOORDS);
}

void OpenGLAPI::disableVertexTangents()
{
	glDisableVertexAttribArray(EAttribLocation::TANGENT);
}

void OpenGLAPI::disableVertexBitangents()
{
	glDisableVertexAttribArray(EAttribLocation::BITANGENT);
}

void OpenGLAPI::disableGUISettings()
{
	glDisableVertexAttribArray(EAttribLocation::POSITION);
	glEnable(GL_DEPTH_TEST);
}

void OpenGLAPI::clearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

uint32_t OpenGLAPI::setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void *data, uint32_t unit, bool genMipmap)
{
	uint32_t result = 0;

	glGenTextures(1, &result);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, result);

	int colorFormat = (bpp == 3) ? GL_RGB : GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);

	GLint minFilterParam = GL_LINEAR;
	if (genMipmap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		minFilterParam = GL_LINEAR_MIPMAP_LINEAR;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterParam);

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
uint32_t OpenGLAPI::loadVertexShader(const std::string &vertexContent)
{
	return this->compileShader(vertexContent, GL_VERTEX_SHADER);
}

uint32_t OpenGLAPI::loadFragmentShader(const std::string &fragmentContent)
{
	return this->compileShader(fragmentContent, GL_FRAGMENT_SHADER);
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

void OpenGLAPI::deleteBuffers(MeshComponent *mesh)
{
	glDeleteBuffers(1, &mesh->ebo);
	glDeleteBuffers(1, &mesh->vbo);
	glDeleteVertexArrays(1, &mesh->vao);
}

uint32_t OpenGLAPI::compileShader(const std::string &source, uint32_t mode)
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

		std::string shaderType = (mode == GL_VERTEX_SHADER) ? "VERTEX SHADER" : "FRAGMENT SHADER";
		throw "[OpenGLAPI] - In shader: " + shaderType + "\n" + error;
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
