#include "Shader.h"

namespace sre
{

Shader::Shader(uint32_t program, uint32_t vertexShader, uint32_t fragmentShader, bool isLit)
        : program(program), vertexShader(vertexShader), fragmentShader(fragmentShader), isLit(isLit)
{ }

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
