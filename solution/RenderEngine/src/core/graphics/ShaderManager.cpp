#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "SingletonsManager.h"

namespace sre
{

void ShaderManager::init()
{
    this->graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
}

void ShaderManager::release()
{
    for (const auto& item : this->shaders)
    {
        this->graphicsWrapper->releaseShader(item.first, item.second->components);
    }

    this->shaders.clear();
}

uint32_t ShaderManager::loadGUIShader()
{
    std::string vertexContent;
    std::string fragmentContent;

    ShaderContentFactory contentFactory;
    contentFactory.createGUIShaderContent(vertexContent, fragmentContent);

    return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadColorShader()
{
    std::string vertexContent;
    std::string fragmentContent;

    ShaderContentFactory contentFactory;
    contentFactory.createColorShaderContent(vertexContent, fragmentContent);

    return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadCustomShader(const std::string& shaderPath)
{
    std::string vertexContent;
    std::string fragmentContent;

    ShaderContentFactory contentFactory;
    contentFactory.loadCustomContent(shaderPath, vertexContent, fragmentContent);

    return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadPointLightDepthShader()
{
    std::string vertexContent;
    std::string fragmentContent;
    std::string geometryContent;

    ShaderContentFactory contentFactory;
    contentFactory.createPointLightDepthShaderContent(vertexContent, fragmentContent, geometryContent);

    uint32_t vertShader = this->graphicsWrapper->loadVertexShader(vertexContent);
    uint32_t fragShader = this->graphicsWrapper->loadFragmentShader(fragmentContent);
    uint32_t geomShader = this->graphicsWrapper->loadGeometryShader(geometryContent);

    uint32_t program = this->graphicsWrapper->createProgram(vertShader, fragShader, geomShader);

    Shader* shader = new Shader{ program, vertShader, fragShader, geomShader};
    this->shaders.emplace(program, shader);

    return program;
}

uint32_t ShaderManager::loadDirectionalLightDepthShader()
{
    std::string vertexContent;
    std::string fragmentContent;

    ShaderContentFactory contentFactory;
    contentFactory.createDirectionalLightDepthShaderContent(vertexContent, fragmentContent);

    return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadPostProcessingShader(PostProcessingComponent* component)
{
	std::string vertexContent;
	std::string fragmentContent;

	ShaderContentFactory contentFactory;
	contentFactory.createPostProcessingShaderContent(component, vertexContent, fragmentContent);

	return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadFinalPassPostProcessingShader(PostProcessingComponent* component)
{
	std::string vertexContent;
	std::string fragmentContent;

	ShaderContentFactory contentFactory;
	contentFactory.createFinalPassPostProcessingShaderContent(component, vertexContent, fragmentContent);

	return this->loadShader(vertexContent, fragmentContent);
}

uint32_t ShaderManager::loadShader(const std::string &vertexContent, const std::string &fragmentContent)
{
    uint32_t vertShader = this->graphicsWrapper->loadVertexShader(vertexContent);
    uint32_t fragShader = this->graphicsWrapper->loadFragmentShader(fragmentContent);

    uint32_t program = this->graphicsWrapper->createProgram(vertShader, fragShader);

    Shader* shader = new Shader{ program, vertShader, fragShader };
    this->shaders.emplace(program, shader);

    return program;
}

void ShaderManager::setupUniformLocation(uint32_t program, ShaderVariables::Type variableKey)
{
    std::string variableName = ShaderVariables::Map.at(variableKey);
    int location = this->graphicsWrapper->getUniformLocation(program, variableName);

	const UPTR<Shader>& shader = this->shaders[program];
    shader->addVariableLocation(variableKey, location);
}

void ShaderManager::setupUniformLocation(uint32_t program, const char *variable)
{
    int location = this->graphicsWrapper->getUniformLocation(program, variable);
    const UPTR<Shader>& shader = this->shaders[program];
    shader->addVariableLocation(variable, location);
}

void ShaderManager::setupAttributeLocation(uint32_t program, ShaderVariables::Type variableKey)
{
    std::string variableName = ShaderVariables::Map.at(variableKey);
    int location = this->graphicsWrapper->getAttributeLocation(program, variableName);
    const UPTR<Shader>& shader = this->shaders[program];
    shader->addVariableLocation(variableKey, location);
}

void ShaderManager::disableVertexAttribute(uint32_t program, ShaderVariables::Type variableKey)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->disableVertexAttribute(shader->variableLocations[variableKey]);
}

void ShaderManager::setInt(uint32_t program, ShaderVariables::Type variableKey, int value)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->setInt(program, shader->variableLocations[variableKey], value);
}

void ShaderManager::setInt(uint32_t program, const char *variable, int value)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->setInt(program, shader->customVariableLocations[variable], value);
}

void ShaderManager::setFloat(uint32_t program, ShaderVariables::Type variableKey, float value)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->setFloat(program, shader->variableLocations[variableKey], value);
}

void ShaderManager::setFloat(uint32_t program, const char *variable, float value)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->setFloat(program, shader->customVariableLocations[variable], value);
}

void ShaderManager::setVec2(uint32_t program, ShaderVariables::Type variableKey, const float* value)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->setVec2(program, shader->variableLocations[variableKey], value);
}

void ShaderManager::setVec2(uint32_t program, const char* variable, const float* value)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->setVec2(program, shader->customVariableLocations[variable], value);
}

void ShaderManager::setVec3(uint32_t program, ShaderVariables::Type variableKey, const float *value)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->setVec3(program, shader->variableLocations[variableKey], value);
}

void ShaderManager::setVec3(uint32_t program, const char *variable, const float *value)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->setVec3(program, shader->customVariableLocations[variable], value);
}

void ShaderManager::setVec4(uint32_t program, ShaderVariables::Type variableKey, const float *value)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->setVec4(program, shader->variableLocations[variableKey], value);
}

void ShaderManager::setMat4(uint32_t program, ShaderVariables::Type variableKey, const float *value)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->setMat4(program, shader->variableLocations[variableKey], value);
}

void ShaderManager::setMat4(uint32_t program, const char *variable, const float *value)
{
    const UPTR<Shader>& shader = this->shaders[program];
    this->graphicsWrapper->setMat4(program, shader->customVariableLocations[variable], value);
}

void ShaderManager::enableShader(uint32_t program)
{
    this->graphicsWrapper->enableShader(program);
}

void ShaderManager::disableShader()
{
    this->graphicsWrapper->disableShader();
}

void ShaderManager::releaseShader(uint32_t program)
{
    if (this->shaders.count(program) > 0)
    {
		UPTR<Shader>& shader = this->shaders[program];
        this->graphicsWrapper->releaseShader(program, shader->components);

	    this->shaders.erase(program);
    }
}

} // namespace
