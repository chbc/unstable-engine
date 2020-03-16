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
    for (const UPTR<Shader> &item : this->shaders)
    {
        this->graphicsWrapper->releaseShader(item->program, item->components);
    }

    this->shaders.clear();
}

Shader *ShaderManager::loadGUIShader()
{
    std::string vertexContent;
    std::string fragmentContent;

    ShaderContentFactory contentFactory;
    contentFactory.createGUIShaderContent(vertexContent, fragmentContent);

    return this->loadShader(vertexContent, fragmentContent);
}

Shader *ShaderManager::loadPointLightDepthShader()
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

    Shader *shader = new Shader{ program, vertShader, fragShader, geomShader};
    this->shaders.emplace_back(shader);

    return shader;
}

Shader *ShaderManager::loadDirectionalLightDepthShader()
{
    std::string vertexContent;
    std::string fragmentContent;

    ShaderContentFactory contentFactory;
    contentFactory.createDirectionalLightDepthShaderContent(vertexContent, fragmentContent);

    return this->loadShader(vertexContent, fragmentContent);
}

Shader* ShaderManager::loadPostProcessingShader(PostProcessingComponent* component)
{
	std::string vertexContent;
	std::string fragmentContent;

	ShaderContentFactory contentFactory;
	contentFactory.createPostProcessingShaderContent(component, vertexContent, fragmentContent);

	return this->loadShader(vertexContent, fragmentContent);
}

Shader* ShaderManager::loadFinalPassPostProcessingShader(PostProcessingComponent* component)
{
	std::string vertexContent;
	std::string fragmentContent;

	ShaderContentFactory contentFactory;
	contentFactory.createFinalPassPostProcessingShaderContent(component, vertexContent, fragmentContent);

	return this->loadShader(vertexContent, fragmentContent);
}

Shader *ShaderManager::loadShader(const std::string &vertexContent, const std::string &fragmentContent)
{
    uint32_t vertShader = this->graphicsWrapper->loadVertexShader(vertexContent);
    uint32_t fragShader = this->graphicsWrapper->loadFragmentShader(fragmentContent);

    uint32_t program = this->graphicsWrapper->createProgram(vertShader, fragShader);

    Shader *shader = new Shader{ program, vertShader, fragShader };
    this->shaders.emplace_back(shader);

    return shader;
}

void ShaderManager::setupUniformLocation(Shader *shader, ShaderVariables::Type variableKey)
{
    std::string variableName = ShaderVariables::Map.at(variableKey);
    int location = this->graphicsWrapper->getUniformLocation(shader->program, variableName);
    shader->addVariableLocation(variableKey, location);
}

void ShaderManager::setupUniformLocation(Shader *shader, const char *variable)
{
    int location = this->graphicsWrapper->getUniformLocation(shader->program, variable);
    shader->addVariableLocation(variable, location);
}

void ShaderManager::setInt(Shader *shader, ShaderVariables::Type variableKey, int value)
{
    this->graphicsWrapper->setInt(shader->program, shader->variableLocations[variableKey], value);
}

void ShaderManager::setInt(Shader *shader, const char *variable, int value)
{
    this->graphicsWrapper->setInt(shader->program, shader->customVariableLocations[variable], value);
}

void ShaderManager::setFloat(Shader *shader, ShaderVariables::Type variableKey, float value)
{
    this->graphicsWrapper->setFloat(shader->program, shader->variableLocations[variableKey], value);
}

void ShaderManager::setFloat(Shader *shader, const char *variable, float value)
{
    this->graphicsWrapper->setFloat(shader->program, shader->customVariableLocations[variable], value);
}

void ShaderManager::setVec3(Shader *shader, ShaderVariables::Type variableKey, const float *value)
{
    this->graphicsWrapper->setVec3(shader->program, shader->variableLocations[variableKey], value);
}

void ShaderManager::setVec3(Shader *shader, const char *variable, const float *value)
{
    this->graphicsWrapper->setVec3(shader->program, shader->customVariableLocations[variable], value);
}

void ShaderManager::setVec4(Shader *shader, ShaderVariables::Type variableKey, const float *value)
{
    this->graphicsWrapper->setVec4(shader->program, shader->variableLocations[variableKey], value);
}

void ShaderManager::setMat4(Shader *shader, ShaderVariables::Type variableKey, const float *value)
{
    this->graphicsWrapper->setMat4(shader->program, shader->variableLocations[variableKey], value);
}

void ShaderManager::setMat4(Shader *shader, const char *variable, const float *value)
{
    this->graphicsWrapper->setMat4(shader->program, shader->customVariableLocations[variable], value);
}

void ShaderManager::enableShader(Shader *shader)
{
    this->graphicsWrapper->enableShader(shader->program);
}

void ShaderManager::disableShader()
{
    this->graphicsWrapper->disableShader();
}

} // namespace
