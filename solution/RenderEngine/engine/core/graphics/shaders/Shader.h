#ifndef _SHADER_H_
#define _SHADER_H_

#include <unordered_map>
#include <string>
#include "ShaderConstants.h"

namespace sre
{

class Shader
{

private:
    uint32_t program;
    uint32_t vertexShader;
    uint32_t fragmentShader;
    uint32_t geometryShader;
    bool isLit;

    std::unordered_map<ShaderVariables::Type, int> variableLocations;
    std::unordered_map<std::string, int> customVariableLocations;

public:
    virtual ~Shader() {}
    int getVariableLocation(ShaderVariables::Type variable);
    int getVariableLocation(const char *variable);

private:
    Shader(uint32_t arg_program, uint32_t arg_vertexShader, uint32_t arg_fragmentShader, bool arg_isLit);
    Shader(uint32_t arg_program, uint32_t arg_vertexShader, uint32_t arg_fragmentShader, uint32_t arg_geometryShader, bool isLit);

    void addVariableLocation(ShaderVariables::Type variable, int location);
    void addVariableLocation(std::string variable, int location);

friend class ShaderManager;
};

} // namespace

#endif
