#include "Shader.h"

namespace sre
{

Shader::Shader(uint32_t arg_program, uint32_t vertexShader, uint32_t fragmentShader)
        : program(arg_program)
{
    this->components.push_back(vertexShader);
    this->components.push_back(fragmentShader);
}

Shader::Shader(uint32_t arg_program, uint32_t vertexShader, uint32_t fragmentShader, uint32_t geometryShader)
        : program(arg_program)
{
    this->components.push_back(vertexShader);
    this->components.push_back(fragmentShader);
    this->components.push_back(geometryShader);
}

void Shader::addVariableLocation(ShaderVariables::Type variable, int location)
{
    this->variableLocations[variable] = location;
}

void Shader::addVariableLocation(std::string variable, int location)
{
    this->customVariableLocations[variable] = location;
}

int Shader::getVariableLocation(ShaderVariables::Type variable)
{
    return this->variableLocations[variable];
}

int Shader::getVariableLocation(const char *variable)
{
    return this->customVariableLocations[variable];
}

} // namespace
