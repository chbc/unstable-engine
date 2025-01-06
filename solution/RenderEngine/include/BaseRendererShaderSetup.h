#ifndef _BASE_RENDERER_SHADER_SETUP_H_
#define _BASE_RENDERER_SHADER_SETUP_H_

#include "ShaderLightData.h"
#include <glm/vec3.hpp>

namespace sre
{

class ShaderManager;
class AGraphicsWrapper;
class Shader;

class BaseRendererShaderSetup
{
protected:
    ShaderManager *shaderManager;
    AGraphicsWrapper *graphicsWrapper;

    BaseRendererShaderSetup(ShaderManager *arg_shaderManager, AGraphicsWrapper *arg_graphicsWrapper);

public:
    virtual ~BaseRendererShaderSetup() { }

private:
    virtual void onSceneLoaded(Shader *shader);
    virtual void setupShaderValues(Shader *shader);

friend class MeshRenderer;
};

} // namespace

#endif
