#pragma once

#include "ShaderLightData.h"
#include <glm/vec3.hpp>

namespace sre
{

class ShaderManager;
class AGraphicsWrapper;

class BaseRendererShaderSetup
{
protected:
    ShaderManager *shaderManager;
    AGraphicsWrapper *graphicsWrapper;

    BaseRendererShaderSetup(ShaderManager *arg_shaderManager, AGraphicsWrapper *arg_graphicsWrapper);

public:
    virtual ~BaseRendererShaderSetup() { }

private:
    virtual void onSceneLoaded(uint32_t program);
    virtual void setupShaderValues(uint32_t program);

friend class MeshRenderer;
};

} // namespace
