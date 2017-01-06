#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>

#include "ShaderManager.h"

namespace sre
{

ShaderManager::ShaderManager(const SPTR<AGraphicsWrapper> &graphicsWrapper)
{
	this->graphicsWrapper = graphicsWrapper;
}

ShaderManager::~ShaderManager()
{
	this->graphicsWrapper->releaseShaders(this->vertShaders, this->fragShaders, this->programs);
}

uint32_t ShaderManager::loadShader(const std::string &vertexFile, const std::string &fragmentFile)
{
	uint32_t vertShader = this->graphicsWrapper->loadVertexShader(vertexFile);
	uint32_t fragShader = this->graphicsWrapper->loadFragmentShader(fragmentFile);

	uint32_t program = this->graphicsWrapper->createProgram(vertShader, fragShader);

	this->vertShaders.push(vertShader);
	this->fragShaders.push(fragShader);
	this->programs.push(program);
	
	return program;
}

// passing values //
void ShaderManager::setInt(uint32_t program, const std::string &varName, int value)
{
	this->graphicsWrapper->setInt(program, varName, value);
}

void ShaderManager::setVec3(uint32_t program, const std::string &varName, float *value)
{
	this->graphicsWrapper->setVec3(program, varName, value);
}

void ShaderManager::setVec4(uint32_t program, const std::string &varName, float *value)
{
	this->graphicsWrapper->setVec4(program, varName, value);
}

void ShaderManager::setMat4(uint32_t program, const std::string &varName, float *value)
{
	this->graphicsWrapper->setMat4(program, varName, value);
}

int ShaderManager::getAttribLocation(uint32_t program, EShaderVariable::Type shaderVariable)
{
	int result = -1;

	switch (shaderVariable)
	{
		case EShaderVariable::SHADER_POSITION:   result = 0; break;
		case EShaderVariable::SHADER_NORMAL:     result = 1; break;
		default: break;
	}

	return result;
}

// attributes
/*
void ShaderManager::setAttributeValue(const char *idName, float x)
{
	uint32_t location = glGetAttribLocation(this->program, idName);
	glUniform1f(location, x);
}

void ShaderManager::setAttributeValue(const char *idName, float x, float y)
{
	uint32_t location = glGetAttribLocation(this->program, idName);
	glUniform2f(location, x, y);
}

void ShaderManager::setAttributeValue(const char *idName, float x, float y, float z)
{
	uint32_t location = glGetAttribLocation(this->program, idName);
	glUniform3f(location, x, y, z);
}
*/

void ShaderManager::enableShader(uint32_t program)
{
	this->graphicsWrapper->enableShader(program);
}

void ShaderManager::disableShader()
{
	this->graphicsWrapper->disableShader();
}

} // namespace
