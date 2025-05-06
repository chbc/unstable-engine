#ifdef __ANDROID__

#include "OpenGLESAPI.h"
#include "MeshData.h"
#include "GUIImageComponent.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"

#include "SDL_test_common.h"

#define HAVE_OPENGLES2

#include "SDL_opengles2.h"

#define GL_CHECK(x) \
        x; \
        { \
          GLenum glError = glGetError(); \
          if(glError != GL_NO_ERROR) { \
            SDL_Log("XXX glGetError() = %i (0x%.8x) at line %i\n", glError, glError, __LINE__); \
          } \
        }

namespace sre
{

void OpenGLESAPI::init()
{
	GL_CHECK(glClearColor(0.1f, 0.1f, 0.2f, 1.0f));

	GL_CHECK(glEnable(GL_CULL_FACE));
	GL_CHECK(glEnable(GL_DEPTH_TEST));

	GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GL_CHECK(glEnable(GL_BLEND));
}

void OpenGLESAPI::createVAO(MeshData* meshData)
{
	int dataSize = meshData->vertexData.size();
	GL_CHECK(glGenBuffers(1, &meshData->vbo));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, meshData->vbo));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(VertexData), &meshData->vertexData[0], GL_STATIC_DRAW));
}

void OpenGLESAPI::createEBO(MeshData* meshData)
{
	GL_CHECK(glGenBuffers(1, &meshData->ebo));
	int size = meshData->indices.size();

	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->ebo));
	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), &meshData->indices[0], GL_STATIC_DRAW));
}

void OpenGLESAPI::createGUIVAO(MeshData2D* meshData, uint32_t maxItems, bool isDynamic)
{
	void* data = nullptr;
	int size = maxItems * 4;
	GLenum usage = GL_DYNAMIC_DRAW;

	// data
	if (!isDynamic)
	{
		data = &meshData->vertexData[0];
		size = meshData->vertexData.size();
		usage = GL_STATIC_DRAW;
	}

	// VBO
	GL_CHECK(glGenBuffers(1, &meshData->vbo));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, meshData->vbo));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size * sizeof(VertexData2D), data, usage));
}

void OpenGLESAPI::createGUIEBO(MeshData2D* meshData, uint32_t maxItems, bool isDynamic)
{
	void* data = nullptr;
	int size = maxItems * 6;
	GLenum usage = GL_DYNAMIC_DRAW;

	if (!isDynamic)
	{
		data = &meshData->indices[0];
		size = meshData->indices.size();
		usage = GL_STATIC_DRAW;
	}

	// EBO
	GL_CHECK(glGenBuffers(1, &meshData->ebo));
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->ebo));
	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), data, usage));
}

void OpenGLESAPI::bindVAO(uint32_t vao, uint32_t vbo)
{
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
}

void OpenGLESAPI::setVertexAttributePointer(int attributeLocation, size_t itemSize, size_t dataSize, void* dataOffset)
{
	GL_CHECK(glEnableVertexAttribArray(attributeLocation));
	GL_CHECK(glVertexAttribPointer(attributeLocation, itemSize, GL_FLOAT, GL_FALSE, dataSize, dataOffset));
}

void OpenGLESAPI::enableGUISettings()
{
	/* XXX APAGAR
	GL_CHECK(glEnableVertexAttribArray(EAttribLocation::TEXCOORDS));
	GL_CHECK(glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData2D), ABaseVertexData::getUVOffset()));
	GL_CHECK(glEnableVertexAttribArray(EAttribLocation::POSITION));
	GL_CHECK(glVertexAttribPointer(EAttribLocation::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData2D), VertexData2D::getPositionOffset()));

	GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GL_CHECK(glEnable(GL_BLEND));
	*/
}

void OpenGLESAPI::enablePostProcessingSettings()
{
	// XXX APAGAR
}

void OpenGLESAPI::enableVertexPositions()
{
	/* XXX APAGAR
	GL_CHECK(glEnableVertexAttribArray(EAttribLocation::POSITION));
	GL_CHECK(glVertexAttribPointer(EAttribLocation::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getPositionOffset()));
	*/
}

void OpenGLESAPI::enableVertexNormals() { }

void OpenGLESAPI::enableTexCoords()
{
	/* XXX
	GL_CHECK(glEnableVertexAttribArray(EAttribLocation::TEXCOORDS));
	GL_CHECK(glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), ABaseVertexData::getUVOffset()));

	GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GL_CHECK(glEnable(GL_BLEND));
	*/
}

void OpenGLESAPI::enableVertexTangents() { }

void OpenGLESAPI::enableVertexBitangents() { }

void OpenGLESAPI::activateGUITexture(uint32_t textureId)
{
	GL_CHECK(glActiveTexture(GL_TEXTURE0));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureId));
}

void OpenGLESAPI::activateDiffuseTexture(uint32_t textureId)
{
	GL_CHECK(glActiveTexture(GL_TEXTURE1));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureId));
}

void OpenGLESAPI::activateNormalTexture(uint32_t textureId) { }

void OpenGLESAPI::activateSpecularTexture(uint32_t textureId) { }

void OpenGLESAPI::activateAOTexture(uint32_t textureId) { }

void OpenGLESAPI::activateShadowMapTexture(uint32_t textureId, uint32_t unit, bool cubeMap) { }

void OpenGLESAPI::setupBufferSubData(MeshData2D* meshData)
{
	uint32_t size = meshData->indices.size() * sizeof(uint32_t);
	GL_CHECK(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, &meshData->indices[0]));

	size = meshData->vertexData.size() * sizeof(VertexData2D);
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, size, &meshData->vertexData[0]));
}

void OpenGLESAPI::drawElement(uint32_t indicesId, size_t indicesSize)
{
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId));
	GL_CHECK(glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr));
}

void OpenGLESAPI::disableVertexAttribute(int location)
{
	GL_CHECK(glDisableVertexAttribArray(location));
}

void OpenGLESAPI::enableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void OpenGLESAPI::disableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}

void OpenGLESAPI::disableVertexPositions()
{
}

void OpenGLESAPI::disableVertexNormals() { }

void OpenGLESAPI::disableTexCoords()
{
}

void OpenGLESAPI::disableVertexTangents() { }

void OpenGLESAPI::disableVertexBitangents() { }

void OpenGLESAPI::disableGUISettings()
{
}

void OpenGLESAPI::disablePostProcessingSettings() { }

void OpenGLESAPI::clearColorBuffer()
{
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void OpenGLESAPI::clearDepthBuffer()
{
	GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
}

void OpenGLESAPI::clearColorAndDepthBuffer()
{
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

uint32_t OpenGLESAPI::setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void* data, uint32_t unit, bool genMipmap)
{
	uint32_t result{ 0 };

	GL_CHECK(glGenTextures(1, &result));

	GL_CHECK(glActiveTexture(GL_TEXTURE0 + unit));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, result));

	int colorFormat = (bpp == 3) ? GL_RGB : GL_RGBA;

	glTexImage2D
	(
		GL_TEXTURE_2D, 0, colorFormat, width, height,
		0, colorFormat, GL_UNSIGNED_BYTE, data
	);

	GLint minFilterParam = GL_LINEAR;
	if (genMipmap)
	{
		GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
		minFilterParam = GL_LINEAR_MIPMAP_LINEAR;
	}

	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterParam));

	return result;
}

void OpenGLESAPI::deleteTexture(uint32_t id)
{
	GL_CHECK(glDeleteTextures(1, &id));
}

uint32_t OpenGLESAPI::loadVertexShader(const std::string& vertexContent)
{
	return this->compileShader(vertexContent, GL_VERTEX_SHADER);
}

uint32_t OpenGLESAPI::loadFragmentShader(const std::string& fragmentContent)
{
	return this->compileShader(fragmentContent, GL_FRAGMENT_SHADER);
}

uint32_t OpenGLESAPI::loadGeometryShader(const std::string& geometryContent)
{
	SDL_Log("XXX OpenGL ES doesn't support geometry shader!");
	return 0;
}

uint32_t OpenGLESAPI::createProgram(uint32_t vertexShader, uint32_t fragmentShader)
{
	uint32_t program = GL_CHECK(glCreateProgram());
	GL_CHECK(glAttachShader(program, vertexShader));
	GL_CHECK(glAttachShader(program, fragmentShader));

	GL_CHECK(glLinkProgram(program));
	this->checkProgramLink(program);

	return program;
}

uint32_t OpenGLESAPI::createProgram(uint32_t vertexShader, uint32_t fragmentShader, uint32_t geometryShader)
{
	return 0;
}

int OpenGLESAPI::getUniformLocation(uint32_t program, const std::string& varName)
{
	int result = GL_CHECK(glGetUniformLocation(program, varName.c_str()));
	this->checkVariableLocation(result, varName);

	return result;
}

int OpenGLESAPI::getAttributeLocation(uint32_t program, const std::string& varName)
{
	int result = GL_CHECK(glGetAttribLocation(program, varName.c_str()));
	this->checkVariableLocation(result, varName);

	return result;
}

void OpenGLESAPI::setInt(uint32_t program, int location, int value)
{
	GL_CHECK(glUniform1i(location, value));
}

void OpenGLESAPI::setFloat(uint32_t program, int location, float value)
{
	GL_CHECK(glUniform1f(location, value));
}

void OpenGLESAPI::setVec2(uint32_t program, int location, const float* value)
{
	GL_CHECK(glUniform2fv(location, 1, value));
}

void OpenGLESAPI::setVec3(uint32_t program, int location, const float* value)
{
	GL_CHECK(glUniform3fv(location, 1, value));
}

void OpenGLESAPI::setVec4(uint32_t program, int location, const float* value)
{
	GL_CHECK(glUniform4fv(location, 1, value));
}

void OpenGLESAPI::setMat4(uint32_t program, int location, const float* value)
{
	GL_CHECK(glUniformMatrix4fv(location, 1, GL_FALSE, value));
}

void OpenGLESAPI::enableShader(uint32_t program)
{
	GL_CHECK(glUseProgram(program));
}

void OpenGLESAPI::disableShader()
{
	GL_CHECK(glUseProgram(0));
}

void OpenGLESAPI::releaseShader(uint32_t program, std::vector<uint32_t>& components)
{
	for (uint32_t item : components)
	{
		GL_CHECK(glDetachShader(program, item));
		GL_CHECK(glDeleteShader(item));
	}

	GL_CHECK(glDeleteProgram(program));
}

void OpenGLESAPI::deleteBuffers(AMeshData* meshData)
{
	GL_CHECK(glDeleteBuffers(1, &meshData->ebo));
	GL_CHECK(glDeleteBuffers(1, &meshData->vbo));
}

void OpenGLESAPI::bindFrameBuffer(uint32_t fbo) { }

void OpenGLESAPI::unbindFrameBuffer() { }

void OpenGLESAPI::deleteFrameBuffer(uint32_t fbo)
{
	glDeleteFramebuffers(1, fbo);
}

void OpenGLESAPI::setViewport(uint32_t width, uint32_t height)
{
	GL_CHECK(glViewport(0, 0, width, height));
}

uint32_t OpenGLESAPI::compileShader(const std::string& source, uint32_t mode)
{
	uint32_t id = GL_CHECK(glCreateShader(mode));
	const char* csource = source.c_str();

	GL_CHECK(glShaderSource(id, 1, &csource, NULL));
	GL_CHECK(glCompileShader(id));

	int result;
	GL_CHECK(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		char error[1000];
		GL_CHECK(glGetShaderInfoLog(id, 1000, NULL, error));

		std::string shaderType = "UNKNOWN";
		switch (mode)
		{
		case GL_VERTEX_SHADER:      shaderType = "VERTEX_SHADER"; break;
		case GL_FRAGMENT_SHADER:    shaderType = "FRAGMENT_SHADER"; break;
		}

		SDL_Log("XXX [OpenGLAPI] - In shader: %s | %s", shaderType.c_str(), error);
	}

	return id;
}

void OpenGLESAPI::checkVariableLocation(int location, const std::string& varName)
{
	if (location == -1)
		SDL_Log("XXX [OpenGLAPI] Invalid shader variable: %s", varName.c_str());
}

void OpenGLESAPI::checkProgramLink(uint32_t program)
{
	int result = 0;
	GL_CHECK(glGetProgramiv(program, GL_LINK_STATUS, &result));
	if (result == GL_FALSE)
	{
		char error[1000];
		GL_CHECK(glGetProgramInfoLog(program, 1000, NULL, error));

		GL_CHECK(glDeleteProgram(program));

		SDL_Log("XXX [OpenGLAPI] - %s", error);
	}
}

} // namespace
#endif
