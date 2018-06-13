#include <windows.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include "OpenGLAPI.h"
#include <engine/entities/components/renderables/meshes/MeshComponent.h>
#include <engine/entities/components/renderables/gui/GUIImageComponent.h>
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
	int dataSize = mesh->meshData->vertexData.size();

	// VAO
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	// VBO
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->meshData->vertexData.size() * sizeof(VertexData), &mesh->meshData->vertexData[0], GL_STATIC_DRAW);
}

void OpenGLAPI::createEBO(MeshComponent *mesh)
{
	// EBO
	glGenBuffers(1, &mesh->ebo);
	int size = mesh->meshData->indices.size();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), &mesh->meshData->indices[0], GL_STATIC_DRAW);
}

void OpenGLAPI::createGUIVAO(GUIImageComponent *guiComponent)
{
    void *data = nullptr;
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
}

void OpenGLAPI::createGUIEBO(GUIImageComponent *guiComponent)
{
    void *data = nullptr;
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

void OpenGLAPI::enableVertexPositions()
{
	glEnableVertexAttribArray(EAttribLocation::POSITION);
	glVertexAttribPointer(EAttribLocation::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getPositionOffset());
}

void OpenGLAPI::enableVertexNormals()
{
	int offset = sizeof(glm::vec3) + (sizeof(float) * 2);
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
	int offset = (sizeof(glm::vec3) * 2) + (sizeof(float) * 2);
	glEnableVertexAttribArray(EAttribLocation::TANGENT);
	glVertexAttribPointer(EAttribLocation::TANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getTangentOffset());
}

void OpenGLAPI::enableVertexBitangents()
{
	int offset = (sizeof(glm::vec3) * 3) + (sizeof(float) * 2);
	glEnableVertexAttribArray(EAttribLocation::BITANGENT);
	glVertexAttribPointer(EAttribLocation::BITANGENT, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), VertexData::getBitangentOffset());
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

void OpenGLAPI::activateShadowMapTexture(uint32_t textureId)
{
    glActiveTexture(GL_TEXTURE4); // ###
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
}

void OpenGLAPI::setupBufferSubData(const MeshData<GUIVertexData> *meshData)
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

void OpenGLAPI::clearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLAPI::clearDepthBuffer()
{
    glClear(GL_DEPTH_BUFFER_BIT);
}

uint32_t OpenGLAPI::setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void *data, uint32_t unit, bool genMipmap)
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

// ### sombra
uint32_t OpenGLAPI::setupTexture(uint32_t width, uint32_t height, uint32_t unit)
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
uint32_t OpenGLAPI::loadVertexShader(const std::string &vertexContent)
{
	return this->compileShader(vertexContent, GL_VERTEX_SHADER);
}

uint32_t OpenGLAPI::loadFragmentShader(const std::string &fragmentContent)
{
	return this->compileShader(fragmentContent, GL_FRAGMENT_SHADER);
}

uint32_t OpenGLAPI::loadGeometryShader(const std::string &geometryContent)
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

int OpenGLAPI::getUniformLocation(uint32_t program, const std::string &varName)
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

void OpenGLAPI::setVec3(uint32_t program, int location, const float *value)
{
	glUniform3fv(location, 1, value);
}

void OpenGLAPI::setVec4(uint32_t program, int location, const float *value)
{
	glUniform4fv(location, 1, value);
}

void OpenGLAPI::setMat4(uint32_t program, int location, const float *value)
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

void OpenGLAPI::releaseShader(uint32_t program, uint32_t vertShader, uint32_t fragShader)
{
    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    glDeleteProgram(program);
}

void OpenGLAPI::deleteBuffers(MeshComponent *mesh)
{
    glDeleteBuffers(1, &mesh->ebo);
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteVertexArrays(1, &mesh->vao);
}

void OpenGLAPI::deleteBuffers(GUIImageComponent *guiComponent)
{
    glDeleteBuffers(1, &guiComponent->ebo);
    glDeleteBuffers(1, &guiComponent->vbo);
    glDeleteVertexArrays(1, &guiComponent->vao);
}

// ###
void OpenGLAPI::generateFrameBuffer(uint32_t &fbo, uint32_t textureId, bool cubemap)
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
        throw "[OpenGLAPI] - Framebuffer error!";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// ###
void OpenGLAPI::bindFrameBuffer(uint32_t fbo)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

// ###
void OpenGLAPI::unbindFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// ###
void OpenGLAPI::setViewport(uint32_t width, uint32_t height)
{
    glViewport(0, 0, width, height);
}

void OpenGLAPI::enableFrontCullFace()
{
    glCullFace(GL_FRONT);
}

void OpenGLAPI::disableFrontCullFace() 
{
    glCullFace(GL_BACK);
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

unsigned int quadVAO = 0;
unsigned int quadVBO;
void OpenGLAPI::renderQuad()
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
