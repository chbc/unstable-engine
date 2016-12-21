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

unsigned int ShaderManager::loadShader(const std::string &vertexFile, const std::string &fragmentFile)
{
	unsigned int vertShader = this->graphicsWrapper->loadVertexShader(vertexFile);
	unsigned int fragShader = this->graphicsWrapper->loadFragmentShader(fragmentFile);

	unsigned int program = this->graphicsWrapper->createProgram(vertShader, fragShader);

	this->vertShaders.push(vertShader);
	this->fragShaders.push(fragShader);
	this->programs.push(program);

	return program;
}

// passing values //
void ShaderManager::setValue(unsigned int program, const std::string &varName, float x)
{
	this->graphicsWrapper->setValue(program, varName, x);
}

void ShaderManager::setValue(unsigned int program, const std::string &varName, float x, float y)
{
	this->graphicsWrapper->setValue(program, varName, x, y);
}

void ShaderManager::setValue(unsigned int program, const std::string &varName, float x, float y, float z)
{
	this->graphicsWrapper->setValue(program, varName, x, y, z);
}

void ShaderManager::setValue(unsigned int program, const std::string &varName, float x, float y, float z, float w)
{
	this->graphicsWrapper->setValue(program, varName, x, y, z, w);
}

void ShaderManager::setValue(unsigned int program, const std::string &varName, float *matrix)
{
	this->graphicsWrapper->setValue(program, varName, matrix);
}

void ShaderManager::setValue(unsigned int program, const std::string &varName, int value)
{
	this->graphicsWrapper->setValue(program, varName, value);
}

int ShaderManager::getAttribLocation(unsigned int program, EShaderVariable::Type shaderVariable)
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
	unsigned int location = glGetAttribLocation(this->program, idName);
	glUniform1f(location, x);
}

void ShaderManager::setAttributeValue(const char *idName, float x, float y)
{
	unsigned int location = glGetAttribLocation(this->program, idName);
	glUniform2f(location, x, y);
}

void ShaderManager::setAttributeValue(const char *idName, float x, float y, float z)
{
	unsigned int location = glGetAttribLocation(this->program, idName);
	glUniform3f(location, x, y, z);
}
*/

void ShaderManager::enableShader(unsigned int program)
{
	this->graphicsWrapper->enableShader(program);
}

void ShaderManager::disableShader()
{
	this->graphicsWrapper->disableShader();
}

} // namespace
