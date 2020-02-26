#include <windows.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include "OpenGLAPI.h"
#include "MeshData.h"
#include "SingletonsManager.h"
#include "MultimediaManager.h"

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
		this->multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw std::string("GLEW didn't inited");

		const GLubyte * glVersion = glGetString(GL_VERSION);
		std::string strGLVersion((char*)(glVersion));
		multimediaManager->logMessage("OpenGL Version: " + strGLVersion);

		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLAPI::createVAO(MeshData* meshData)
	{
		// data
		int dataSize = meshData->vertexData.size();

		// VAO
		glGenVertexArrays(1, &meshData->vao);
		glBindVertexArray(meshData->vao);

		// VBO
		glGenBuffers(1, &meshData->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, meshData->vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(VertexData), &meshData->vertexData[0], GL_STATIC_DRAW);
	}

	void OpenGLAPI::createEBO(MeshData* meshData)
	{
		// EBO
		glGenBuffers(1, &meshData->ebo);
		int size = meshData->indices.size();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), &meshData->indices[0], GL_STATIC_DRAW);
	}

	void OpenGLAPI::createGUIVAO(GUIMeshData* meshData, uint32_t maxItems, bool isDynamic)
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

		// VAO
		glGenVertexArrays(1, &meshData->vao);
		glBindVertexArray(meshData->vao);

		// VBO
		glGenBuffers(1, &meshData->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, meshData->vbo);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(GUIVertexData), data, usage);
	}

	void OpenGLAPI::createGUIEBO(GUIMeshData* meshData, uint32_t maxItems, bool isDynamic)
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
		glGenBuffers(1, &meshData->ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), data, usage);
	}

	void OpenGLAPI::bindVAO(uint32_t vao, uint32_t vbo)
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	void OpenGLAPI::enableGUISettings()
	{
		glEnableVertexAttribArray(EAttribLocation::TEXCOORDS);
		glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertexData), ABaseVertexData::getUVOffset());
		glEnableVertexAttribArray(EAttribLocation::POSITION);
		glVertexAttribPointer(EAttribLocation::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertexData), GUIVertexData::getPositionOffset());

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	void OpenGLAPI::enablePostProcessingSettings()
	{
		glEnableVertexAttribArray(EAttribLocation::TEXCOORDS);
		glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertexData), ABaseVertexData::getUVOffset());
		glEnableVertexAttribArray(EAttribLocation::POSITION);
		glVertexAttribPointer(EAttribLocation::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertexData), GUIVertexData::getPositionOffset());
	}

	void OpenGLAPI::enableVertexPositions()
	{
		glEnableVertexAttribArray(EAttribLocation::POSITION);
		glVertexAttribPointer(EAttribLocation::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getPositionOffset());
	}

	void OpenGLAPI::enableVertexNormals()
	{
		glEnableVertexAttribArray(EAttribLocation::NORMAL);
		glVertexAttribPointer(EAttribLocation::NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getNormalOffset());
	}

	void OpenGLAPI::enableTexCoords()
	{
		glEnableVertexAttribArray(EAttribLocation::TEXCOORDS);
		glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), ABaseVertexData::getUVOffset());
	}

	void OpenGLAPI::enableVertexTangents()
	{
		glEnableVertexAttribArray(EAttribLocation::TANGENT);
		glVertexAttribPointer(EAttribLocation::TANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getTangentOffset());
	}

	void OpenGLAPI::enableVertexBitangents()
	{
		glEnableVertexAttribArray(EAttribLocation::BITANGENT);
		glVertexAttribPointer(EAttribLocation::BITANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getBitangentOffset());
	}

	void OpenGLAPI::activateGUITexture(uint32_t textureId)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGLAPI::activateDiffuseTexture(uint32_t textureId)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGLAPI::activateNormalTexture(uint32_t textureId)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGLAPI::activateSpecularTexture(uint32_t textureId)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGLAPI::activateAOTexture(uint32_t textureId)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGLAPI::activateShadowMapTexture(uint32_t textureId, uint32_t unit, bool cubeMap)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(cubeMap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, textureId);
	}

	void OpenGLAPI::setupBufferSubData(GUIMeshData* meshData)
	{
		uint32_t size = meshData->indices.size() * sizeof(uint32_t);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, &meshData->indices[0]);

		size = meshData->vertexData.size() * sizeof(GUIVertexData);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, &meshData->vertexData[0]);
	}

	void OpenGLAPI::drawElement(uint32_t indicesSize)
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
		glDisable(GL_BLEND);
	}

	void OpenGLAPI::disablePostProcessingSettings()
	{
		glDisableVertexAttribArray(EAttribLocation::POSITION);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLAPI::clearColorBuffer()
	{
		glDisable(GL_DEPTH_TEST);
		// ### glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLAPI::clearDepthBuffer()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLAPI::clearColorAndDepthBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	uint32_t OpenGLAPI::setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void* data, uint32_t unit, bool genMipmap)
	{
		uint32_t result{ 0 };

		glGenTextures(1, &result);

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, result);

		int colorFormat = (bpp == 3) ? GL_RGB : GL_RGBA;

		glTexImage2D
		(
			GL_TEXTURE_2D, 0, colorFormat, width, height,
			0, colorFormat, GL_UNSIGNED_BYTE, data
		);

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

	uint32_t OpenGLAPI::createTexture(uint32_t width, uint32_t height, uint32_t unit)
	{
		uint32_t result{ 0 };
		glGenTextures(1, &result);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, result);
		glTexImage2D
		(
			GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height,
			0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		return result;
	}

	uint32_t OpenGLAPI::createTexture(uint32_t width, uint32_t height)
	{
		uint32_t result;
		glGenTextures(1, &result);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, result);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return result;
	}

	uint32_t OpenGLAPI::generateCubemap(uint32_t width, uint32_t height, uint32_t unit)
	{
		uint32_t result{ 0 };

		glGenTextures(1, &result);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, result);

		for (uint32_t i = 0; i < 6; i++)
		{
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height,
				0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr
			);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

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
	uint32_t OpenGLAPI::loadVertexShader(const std::string & vertexContent)
	{
		return this->compileShader(vertexContent, GL_VERTEX_SHADER);
	}

	uint32_t OpenGLAPI::loadFragmentShader(const std::string & fragmentContent)
	{
		return this->compileShader(fragmentContent, GL_FRAGMENT_SHADER);
	}

	uint32_t OpenGLAPI::loadGeometryShader(const std::string & geometryContent)
	{
		return this->compileShader(geometryContent, GL_GEOMETRY_SHADER);
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

	uint32_t OpenGLAPI::createProgram(uint32_t vertexShader, uint32_t fragmentShader, uint32_t geometryShader)
	{
		uint32_t program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glAttachShader(program, geometryShader);

		glLinkProgram(program);
		this->checkProgramLink(program);

		return program;
	}

	int OpenGLAPI::getUniformLocation(uint32_t program, const std::string & varName)
	{
		int result = glGetUniformLocation(program, varName.c_str());
		this->checkVariableLocation(result, varName);

		return result;
	}

	void OpenGLAPI::setInt(uint32_t program, int location, int value)
	{
		glUniform1i(location, value);
	}

	void OpenGLAPI::setFloat(uint32_t program, int location, float value)
	{
		glUniform1f(location, value);
	}

	void OpenGLAPI::setVec3(uint32_t program, int location, const float* value)
	{
		glUniform3fv(location, 1, value);
	}

	void OpenGLAPI::setVec4(uint32_t program, int location, const float* value)
	{
		glUniform4fv(location, 1, value);
	}

	void OpenGLAPI::setMat4(uint32_t program, int location, const float* value)
	{
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

	void OpenGLAPI::releaseShader(uint32_t program, std::vector<uint32_t> components)
	{
		for (uint32_t item : components)
		{
			glDetachShader(program, item);
			glDeleteShader(item);
		}

		glDeleteProgram(program);
	}

	void OpenGLAPI::deleteBuffers(AMeshData* meshData)
	{
		glDeleteBuffers(1, &meshData->ebo);
		glDeleteBuffers(1, &meshData->vbo);
		glDeleteVertexArrays(1, &meshData->vao);
	}

	uint32_t OpenGLAPI::generateDepthFrameBuffer(uint32_t textureId, bool cubemap)
	{
		uint32_t result;
		glGenFramebuffers(1, &result);

		glBindFramebuffer(GL_FRAMEBUFFER, result);

		if (cubemap)
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureId, 0);
		else
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureId, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw "[OpenGLAPI] - Depth framebuffer error!";

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return result;
	}

	uint32_t OpenGLAPI::generateColorFrameBuffer(uint32_t textureId, uint32_t width, uint32_t height)
	{
		uint32_t result;
		glGenFramebuffers(1, &result);
		glBindFramebuffer(GL_FRAMEBUFFER, result);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw "[OpenGLAPI] - Color framebuffer error!";

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return result;
	}

	void OpenGLAPI::bindFrameBuffer(uint32_t fbo)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}

	void OpenGLAPI::unbindFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLAPI::setViewport(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}

	uint32_t OpenGLAPI::compileShader(const std::string & source, uint32_t mode)
	{
		uint32_t id = glCreateShader(mode);
		const char* csource = source.c_str();

		glShaderSource(id, 1, &csource, NULL);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			char error[1000];
			glGetShaderInfoLog(id, 1000, NULL, error);

			std::string shaderType = "UNKNOWN";
			switch (mode)
			{
			case GL_VERTEX_SHADER:      shaderType = "VERTEX_SHADER"; break;
			case GL_FRAGMENT_SHADER:    shaderType = "FRAGMENT_SHADER"; break;
			case GL_GEOMETRY_SHADER:    shaderType = "GEOMETRY_SHADER"; break;
			}

			//= (mode == GL_VERTEX_SHADER) ? "VERTEX SHADER" : "FRAGMENT SHADER";
			throw "[OpenGLAPI] - In shader: " + shaderType + "\n" + error;
		}

		return id;
	}

	void OpenGLAPI::checkVariableLocation(int location, const std::string & varName)
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

	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	void OpenGLAPI::DEBUG_renderQuad()
	{
		if (quadVAO == 0)
		{
			float w = 1.0f;

			float quadVertices[] = {
				// positions        // texture Coords
				-w,  1.0f, 0.0f, 0.0f, 1.0f,
				-w, -1.0f, 0.0f, 0.0f, 0.0f,
				w,  1.0f, 0.0f, 1.0f, 1.0f,
				w, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			// setup plane VAO
			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		}
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	//

} // namespace
