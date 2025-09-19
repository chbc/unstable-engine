#include "Shader.h"

namespace sre
{

Shader::Shader(uint32_t arg_program, const std::vector<uint32_t>& arg_components)
	: program(arg_program), components(arg_components)
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
