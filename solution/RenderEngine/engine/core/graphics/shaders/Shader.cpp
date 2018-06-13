#include "Shader.h"

namespace sre
{

Shader::Shader(uint32_t arg_program, uint32_t arg_vertexShader, uint32_t arg_fragmentShader, bool arg_isLit)
        : program(arg_program), vertexShader(arg_vertexShader), fragmentShader(arg_fragmentShader), isLit(arg_isLit)
{ }

Shader::Shader(uint32_t arg_program, uint32_t arg_vertexShader, uint32_t arg_fragmentShader, uint32_t arg_geometryShader, bool arg_isLit)
        : program(arg_program), vertexShader(arg_vertexShader), fragmentShader(arg_fragmentShader), isLit(arg_isLit)
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
