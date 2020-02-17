#include <windows.h>
#define GLEW_STATIC
#include <GL/glew.h>

#include "OpenGLESAPI.h"
#include "MeshComponent.h"
#include "GUIImageComponent.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"

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

	void OpenGLESAPI::init()
	{
		this->multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();

#ifndef __ANDROID__
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw std::string("GLEW didn't inited");
#endif

		const GLubyte* glVersion = glGetString(GL_VERSION);
		std::string strGLVersion((char*)(glVersion));
		multimediaManager->logMessage("OpenGL Version: " + strGLVersion);

		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLESAPI::createVAO(MeshComponent* mesh)
	{
		/* ###
		// data
		int dataSize = mesh->meshData->vertexData.size();

		// VAO
		glGenVertexArrays(1, &mesh->vao);
		glBindVertexArray(mesh->vao);

		// VBO
		glGenBuffers(1, &mesh->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize * sizeof(VertexData), &mesh->meshData->vertexData[0], GL_STATIC_DRAW);
		*/
	}

	void OpenGLESAPI::createEBO(MeshComponent* mesh)
	{
		/* ###
		// EBO
		glGenBuffers(1, &mesh->ebo);
		int size = mesh->meshData->indices.size();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), &mesh->meshData->indices[0], GL_STATIC_DRAW);
		*/
	}

	void OpenGLESAPI::createGUIVAO(GUIImageComponent* guiComponent)
	{
		/* ###
		void* data = nullptr;
		int size = guiComponent->maxItems * 4;
		GLenum usage = GL_DYNAMIC_DRAW;

		// data
		if (!guiComponent->isDynamic)
		{
			data = &guiComponent->meshData->vertexData[0];
			size = guiComponent->meshData->vertexData.size();
			usage = GL_STATIC_DRAW;
		}

		// VAO
		glGenVertexArrays(1, &guiComponent->vao);
		glBindVertexArray(guiComponent->vao);

		// VBO
		glGenBuffers(1, &guiComponent->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, guiComponent->vbo);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(GUIVertexData), data, usage);
		*/
	}

	void OpenGLESAPI::createGUIEBO(GUIImageComponent* guiComponent)
	{
		/* ###
		void* data = nullptr;
		int size = guiComponent->maxItems * 6;
		GLenum usage = GL_DYNAMIC_DRAW;

		if (!guiComponent->isDynamic)
		{
			data = &guiComponent->meshData->indices[0];
			size = guiComponent->meshData->indices.size();
			usage = GL_STATIC_DRAW;
		}

		// EBO
		glGenBuffers(1, &guiComponent->ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, guiComponent->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), data, usage);
		*/
	}

	void OpenGLESAPI::bindVAO(uint32_t vao, uint32_t vbo)
	{
		/* ###
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		*/
	}

	void OpenGLESAPI::enableGUISettings()
	{
		glEnableVertexAttribArray(EAttribLocation::TEXCOORDS);
		glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertexData), ABaseVertexData::getUVOffset());
		glEnableVertexAttribArray(EAttribLocation::POSITION);
		glVertexAttribPointer(EAttribLocation::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(GUIVertexData), GUIVertexData::getPositionOffset());

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	void OpenGLESAPI::enableVertexPositions()
	{
		/* ###
		glEnableVertexAttribArray(EAttribLocation::POSITION);
		glVertexAttribPointer(EAttribLocation::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getPositionOffset());
		*/
	}

	void OpenGLESAPI::enableVertexNormals()
	{
		glEnableVertexAttribArray(EAttribLocation::NORMAL);
		glVertexAttribPointer(EAttribLocation::NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getNormalOffset());
	}

	void OpenGLESAPI::enableTexCoords()
	{
		glEnableVertexAttribArray(EAttribLocation::TEXCOORDS);
		glVertexAttribPointer(EAttribLocation::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), ABaseVertexData::getUVOffset());
	}

	void OpenGLESAPI::enableVertexTangents()
	{
		glEnableVertexAttribArray(EAttribLocation::TANGENT);
		glVertexAttribPointer(EAttribLocation::TANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getTangentOffset());
	}

	void OpenGLESAPI::enableVertexBitangents()
	{
		glEnableVertexAttribArray(EAttribLocation::BITANGENT);
		glVertexAttribPointer(EAttribLocation::BITANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getBitangentOffset());
	}

	void OpenGLESAPI::activateGUITexture(uint32_t textureId)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGLESAPI::activateDiffuseTexture(uint32_t textureId)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGLESAPI::activateNormalTexture(uint32_t textureId)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGLESAPI::activateSpecularTexture(uint32_t textureId)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGLESAPI::activateAOTexture(uint32_t textureId)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGLESAPI::activateShadowMapTexture(uint32_t textureId, uint32_t unit, bool cubeMap)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(cubeMap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, textureId);
	}

	void OpenGLESAPI::setupBufferSubData(const MeshData<GUIVertexData>* meshData)
	{
		uint32_t size = meshData->indices.size() * sizeof(uint32_t);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, &meshData->indices[0]);

		size = meshData->vertexData.size() * sizeof(GUIVertexData);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, &meshData->vertexData[0]);
	}

	void OpenGLESAPI::drawElement(uint32_t indicesSize)
	{
		static GLfloat vVertices[] = { 0.0f,  0.5f, 0.0f,
								 -0.5f, -0.5f, 0.0f,
								 0.5f, -0.5f, 0.0f
		};

		// Set the viewport
		glViewport(0, 0, 800, 600);

		// Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// ### CONFERIR SE TA USANDO O SHADER

		// Load the vertex data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void OpenGLESAPI::disableVertexPositions()
	{
		glDisableVertexAttribArray(EAttribLocation::POSITION);
	}

	void OpenGLESAPI::disableVertexNormals()
	{
		glDisableVertexAttribArray(EAttribLocation::NORMAL);
	}

	void OpenGLESAPI::disableTexCoords()
	{
		glDisableVertexAttribArray(EAttribLocation::TEXCOORDS);
	}

	void OpenGLESAPI::disableVertexTangents()
	{
		glDisableVertexAttribArray(EAttribLocation::TANGENT);
	}

	void OpenGLESAPI::disableVertexBitangents()
	{
		glDisableVertexAttribArray(EAttribLocation::BITANGENT);
	}

	void OpenGLESAPI::disableGUISettings()
	{
		glDisableVertexAttribArray(EAttribLocation::POSITION);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}

	void OpenGLESAPI::clearBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLESAPI::clearDepthBuffer()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	uint32_t OpenGLESAPI::setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void* data, uint32_t unit, bool genMipmap)
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

	uint32_t OpenGLESAPI::setupTexture(uint32_t width, uint32_t height, uint32_t unit)
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

	uint32_t OpenGLESAPI::generateCubemap(uint32_t width, uint32_t height, uint32_t unit)
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

	void OpenGLESAPI::deleteTexture(uint32_t id)
	{
		glDeleteTextures(1, &id);
	}

	// Shaders
	// ###
	uint32_t OpenGLESAPI::loadVertexShader(const std::string& vertexContent)
	{
		char XXX_VERT[] =
			"#version 300 es                          \n"
			"layout(location = 0) in vec4 vPosition;  \n"
			"void main()                              \n"
			"{                                        \n"
			"   gl_Position = vPosition;              \n"
			"}                                        \n";

		return this->compileShader(XXX_VERT, GL_VERTEX_SHADER);
	}

	// ###
	uint32_t OpenGLESAPI::loadFragmentShader(const std::string& fragmentContent)
	{
		char XXX_FRAG[] =
			"#version 300 es                              \n"
			"precision mediump float;                     \n"
			"out vec4 fragColor;                          \n"
			"void main()                                  \n"
			"{                                            \n"
			"   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
			"}											  \n";

		return this->compileShader(XXX_FRAG, GL_FRAGMENT_SHADER);
	}

	uint32_t OpenGLESAPI::loadGeometryShader(const std::string& geometryContent)
	{
		return this->compileShader(geometryContent, GL_GEOMETRY_SHADER);
	}

	uint32_t OpenGLESAPI::createProgram(uint32_t vertexShader, uint32_t fragmentShader)
	{
		uint32_t program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		this->checkProgramLink(program);

		return program;
	}

	uint32_t OpenGLESAPI::createProgram(uint32_t vertexShader, uint32_t fragmentShader, uint32_t geometryShader)
	{
		uint32_t program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glAttachShader(program, geometryShader);

		glLinkProgram(program);
		this->checkProgramLink(program);

		return program;
	}

	int OpenGLESAPI::getUniformLocation(uint32_t program, const std::string& varName)
	{
		return 0;

		/* ### 
		int result = glGetUniformLocation(program, varName.c_str());
		this->checkVariableLocation(result, varName);

		return result;
		*/
	}

	void OpenGLESAPI::setInt(uint32_t program, int location, int value)
	{
		// ### glUniform1i(location, value);
	}

	void OpenGLESAPI::setFloat(uint32_t program, int location, float value)
	{
		// ### glUniform1f(location, value);
	}

	void OpenGLESAPI::setVec3(uint32_t program, int location, const float* value)
	{
		// ### glUniform3fv(location, 1, value);
	}

	void OpenGLESAPI::setVec4(uint32_t program, int location, const float* value)
	{
		// ### glUniform4fv(location, 1, value);
	}

	void OpenGLESAPI::setMat4(uint32_t program, int location, const float* value)
	{
		// ### glUniformMatrix4fv(location, 1, GL_FALSE, value);
	}

	void OpenGLESAPI::enableShader(uint32_t program)
	{
		glUseProgram(program);
	}

	void OpenGLESAPI::disableShader()
	{
		glUseProgram(0);
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

	void OpenGLESAPI::deleteBuffers(MeshComponent* mesh)
	{
		glDeleteBuffers(1, &mesh->ebo);
		glDeleteBuffers(1, &mesh->vbo);
		glDeleteVertexArrays(1, &mesh->vao);
	}

	void OpenGLESAPI::deleteBuffers(GUIImageComponent* guiComponent)
	{
		glDeleteBuffers(1, &guiComponent->ebo);
		glDeleteBuffers(1, &guiComponent->vbo);
		glDeleteVertexArrays(1, &guiComponent->vao);
	}

	void OpenGLESAPI::generateFrameBuffer(uint32_t& fbo, uint32_t textureId, bool cubemap)
	{
		glGenFramebuffers(1, &fbo);

		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		if (cubemap)
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureId, 0);
		else
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureId, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw "[OpenGLESAPI] - Framebuffer error!";

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLESAPI::bindFrameBuffer(uint32_t fbo)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}

	void OpenGLESAPI::unbindFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLESAPI::setViewport(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}

	uint32_t OpenGLESAPI::compileShader(const std::string& source, uint32_t mode)
	{
		uint32_t id = glCreateShader(mode);
		const char* csource = source.c_str();

		glShaderSource(id, 1, &csource, NULL);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint infoLen = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen > 1)
			{
				char* error = (char*) malloc(sizeof(char) * infoLen);

				glGetShaderInfoLog(id, infoLen, NULL, error);

				std::string shaderType = "UNKNOWN";
				switch (mode)
				{
					case GL_VERTEX_SHADER:      shaderType = "VERTEX_SHADER"; break;
					case GL_FRAGMENT_SHADER:    shaderType = "FRAGMENT_SHADER"; break;
					case GL_GEOMETRY_SHADER:    shaderType = "GEOMETRY_SHADER"; break;
				}

				std::string errorMessage(error);
				errorMessage = "[OpenGLESAPI] - In shader: " + shaderType + "\n" + errorMessage;
				this->multimediaManager->logWarning(errorMessage);

				free(error);
			}

			glDeleteShader(id);

			throw "[OpenGLESAPI] - compileShader";
		}

		return id;
	}

	void OpenGLESAPI::checkVariableLocation(int location, const std::string& varName)
	{
		if (location == -1)
		{
			this->multimediaManager->logWarning("[OpenGLESAPI] Invalid shader variable: " + varName);
			throw "[OpenGLESAPI] - checkVariableLocation";
		}
	}

	void OpenGLESAPI::checkProgramLink(uint32_t program)
	{
		int result = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint infoLen = 0;

			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char* error = (char*) malloc(sizeof(char) * infoLen);

				std::string errorMessage(error);
				errorMessage = "[OpenGLESAPI] - Error linking shader: " + errorMessage;
				this->multimediaManager->logWarning(errorMessage);

				free(error);
			}

			glDeleteProgram(program);
			throw "[OpenGLESAP] - checkProgramLink";
		}
	}
} // namespace
