#include "ShaderManager.h"
#include <engine/systems/wrappers/graphics/AGraphicsWrapper.h>
#include "shaders/ShaderContentFactory.h"

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

uint32_t ShaderManager::loadColorShader()
{
	std::string vertexContent;
	std::string fragmentContent;
	ShaderContentFactory contentFactory;
	contentFactory.createColorContent(vertexContent, fragmentContent);

	return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadDiffuseShader()
{
	std::string vertexContent;
	std::string fragmentContent;
	ShaderContentFactory contentFactory;
	contentFactory.createDiffuseContent(vertexContent, fragmentContent);

	return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadNormalMapShader()
{
	std::string vertexContent;
	std::string fragmentContent;
	ShaderContentFactory contentFactory;
	contentFactory.createNormalMapContent(vertexContent, fragmentContent);

	return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadSpecularMapShader()
{
	std::string vertexContent;
	std::string fragmentContent;
	ShaderContentFactory contentFactory;
	contentFactory.createSpecularMapContent(vertexContent, fragmentContent);

	return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadAOMapShader()
{
	std::string vertexContent;
	std::string fragmentContent;
	ShaderContentFactory contentFactory;
	contentFactory.createAOMapContent(vertexContent, fragmentContent);

	return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadShader(const std::string &vertexContent, const std::string &fragmentContent)
{
	uint32_t vertShader = this->graphicsWrapper->loadVertexShader(vertexContent);
	uint32_t fragShader = this->graphicsWrapper->loadFragmentShader(fragmentContent);

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

void ShaderManager::setFloat(uint32_t program, const std::string &varName, float value)
{
	this->graphicsWrapper->setFloat(program, varName, value);
}

void ShaderManager::setVec3(uint32_t program, const std::string &varName, const float *value)
{
	this->graphicsWrapper->setVec3(program, varName, value);
}

void ShaderManager::setVec4(uint32_t program, const std::string &varName, const float *value)
{
	this->graphicsWrapper->setVec4(program, varName, value);
}

void ShaderManager::setMat4(uint32_t program, const std::string &varName, const float *value)
{
	this->graphicsWrapper->setMat4(program, varName, value);
}

void ShaderManager::enableShader(uint32_t program)
{
	this->graphicsWrapper->enableShader(program);
}

void ShaderManager::disableShader()
{
	this->graphicsWrapper->disableShader();
}

} // namespace
