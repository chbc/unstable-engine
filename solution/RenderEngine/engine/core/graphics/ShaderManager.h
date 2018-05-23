#ifndef _GLSL_SHADER_API_H_
#define _GLSL_SHADER_API_H_

#include <bitset>

#include <engine/core/singletonsManager/ASingleton.h>
#include "engine/utils/memory_aliases.h"
#include "shaders/ShaderContentFactory.h"
#include "shaders/Shader.h"

namespace sre
{

class AGraphicsWrapper;

/*!
	Class to deal with GLSL API
*/
class ShaderManager : ASingleton
{
protected:
	void init() override;
    void release() override;

private:
    VECTOR_UPTR<Shader> shaders;

    AGraphicsWrapper *graphicsWrapper;

    // main load function
    template <size_t SIZE> 
    Shader *loadShader(const std::bitset<SIZE> &componentsBitset)
    {
        std::string vertexContent;
        std::string fragmentContent;

        ShaderContentFactory contentFactory;
        contentFactory.createShaderContent(componentsBitset, vertexContent, fragmentContent);

        return this->loadShader(vertexContent, fragmentContent);
    }

    Shader *loadGUIShader();
    Shader *loadShader(const std::string &vertexContent, const std::string &fragmentContent, bool isLit = true);

    // passing values //
    void setupLightUniformLocations(ShaderVariables::Type variableKey);
    void setupLightUniformLocations(const char *variable);
    void setupUniformLocation(Shader *shader, ShaderVariables::Type variableKey);
    void setupUniformLocation(Shader *shader, const char *variable);

    void setInt(Shader *shader, ShaderVariables::Type variableKey, int value);
    void setFloat(Shader *shader, ShaderVariables::Type variableKey, float value);
    void setFloat(Shader *shader, const char *variable, float value);
    void setVec3(Shader *shader, ShaderVariables::Type variableKey, const float *value);
    void setVec3(Shader *shader, const char *variable, const float *value);
    void setVec4(Shader *shader, ShaderVariables::Type variableKey, const float *value);
    void setMat4(Shader *shader, ShaderVariables::Type variableKey, const float *value);

    void enableShader(Shader *shader);
    void disableShader();

friend class RenderManager;
friend class LightManager;
friend class SingletonsManager;

friend class Renderer;
friend class GUIRenderer;
friend class ColorRendererComponent;
friend class DiffuseRendererComponent;
friend class NormalRendererComponent;
friend class SpecularRendererComponent;
friend class AORendererComponent;
};

} // namespace

#endif
