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

namespace EAttribLocation
{

	enum Type : int
	{
		POSITION = 0,
		TEXCOORDS = 1, // XXX
		NORMAL = 2,
		TANGENT = 3,
		BITANGENT = 4
	};

}

void OpenGLESAPI::init()
{
	int status;

	GL_CHECK(glClearColor(0.1f, 0.1f, 0.2f, 1.0f));

	GL_CHECK(glEnable(GL_CULL_FACE));
	GL_CHECK(glEnable(GL_DEPTH_TEST));
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
	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint16_t), &meshData->indices[0], GL_STATIC_DRAW));
}

void OpenGLESAPI::createGUIVAO(GUIMeshData* meshData, uint32_t maxItems, bool isDynamic) { }

void OpenGLESAPI::createGUIEBO(GUIMeshData* meshData, uint32_t maxItems, bool isDynamic) { }

void OpenGLESAPI::bindVAO(uint32_t vao, uint32_t vbo)
{
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
}

void OpenGLESAPI::enableGUISettings()
{
	GL_CHECK(glEnableVertexAttribArray(EAttribLocation::TEXCOORDS));
	GL_CHECK(glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertexData), ABaseVertexData::getUVOffset()));
	GL_CHECK(glEnableVertexAttribArray(EAttribLocation::POSITION));
	GL_CHECK(glVertexAttribPointer(EAttribLocation::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertexData), GUIVertexData::getPositionOffset()));

	GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GL_CHECK(glEnable(GL_BLEND));
}

void OpenGLESAPI::enablePostProcessingSettings() { }

void OpenGLESAPI::enableVertexPositions()
{
	GL_CHECK(glEnableVertexAttribArray(EAttribLocation::POSITION));
	GL_CHECK(glVertexAttribPointer(EAttribLocation::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getPositionOffset()));
}

void OpenGLESAPI::enableVertexNormals() { }

void OpenGLESAPI::enableTexCoords()
{
	GL_CHECK(glEnableVertexAttribArray(EAttribLocation::TEXCOORDS));
	GL_CHECK(glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), ABaseVertexData::getUVOffset()));
}

void OpenGLESAPI::enableVertexTangents() { }

void OpenGLESAPI::enableVertexBitangents() { }

void OpenGLESAPI::activateGUITexture(uint32_t textureId) { }

void OpenGLESAPI::activateDiffuseTexture(uint32_t textureId)
{
	GL_CHECK(glActiveTexture(GL_TEXTURE1));
	GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureId));
}

void OpenGLESAPI::activateNormalTexture(uint32_t textureId) { }

void OpenGLESAPI::activateSpecularTexture(uint32_t textureId) { }

void OpenGLESAPI::activateAOTexture(uint32_t textureId) { }

void OpenGLESAPI::activateShadowMapTexture(uint32_t textureId, uint32_t unit, bool cubeMap) { }

void OpenGLESAPI::setupBufferSubData(GUIMeshData* meshData) { }

void OpenGLESAPI::drawElement(uint32_t indicesId, uint32_t indicesSize)
{
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId));
	GL_CHECK(glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_SHORT, nullptr));
}

void OpenGLESAPI::disableVertexPositions()
{
	GL_CHECK(glDisableVertexAttribArray(EAttribLocation::POSITION));
}

void OpenGLESAPI::disableVertexNormals() { }

void OpenGLESAPI::disableTexCoords()
{
	GL_CHECK(glDisableVertexAttribArray(EAttribLocation::TEXCOORDS));
}

void OpenGLESAPI::disableVertexTangents() { }

void OpenGLESAPI::disableVertexBitangents() { }

void OpenGLESAPI::disableGUISettings() { }

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
	SDL_Log("%s", vertexContent.c_str());
	return this->compileShader(vertexContent, GL_VERTEX_SHADER);
}

uint32_t OpenGLESAPI::loadFragmentShader(const std::string& fragmentContent)
{
	SDL_Log("%s", fragmentContent.c_str());
	return this->compileShader(fragmentContent, GL_FRAGMENT_SHADER);
}

uint32_t OpenGLESAPI::loadGeometryShader(const std::string& geometryContent)
{
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
	int result = glGetUniformLocation(program, varName.c_str());
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

void OpenGLESAPI::releaseShader(uint32_t program, std::vector<uint32_t> components)
{
	for (uint32_t item : components)
	{
		glDetachShader(program, item);
		glDeleteShader(item);
	}

	glDeleteProgram(program);
}

void OpenGLESAPI::deleteBuffers(AMeshData* meshData)
{
	glDeleteBuffers(1, &meshData->ebo);
	glDeleteBuffers(1, &meshData->vbo);
}

void OpenGLESAPI::bindFrameBuffer(uint32_t fbo) { }

void OpenGLESAPI::unbindFrameBuffer() { }

void OpenGLESAPI::setViewport(uint32_t width, uint32_t height)
{
	glViewport(0, 0, width, height);
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
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		char error[1000];
		glGetProgramInfoLog(program, 1000, NULL, error);

		glDeleteProgram(program);

		SDL_Log("XXX [OpenGLAPI] - %s", error);
	}
}

} // namespace
#endif
