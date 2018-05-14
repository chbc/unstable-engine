#ifndef _COLOR_RENDERER_COMPONENT_H_
#define _COLOR_RENDERER_COMPONENT_H_

#include <stdint.h>

namespace sre
{

class ShaderManager;
class AGraphicsWrapper;

class ColorRendererComponent
{
protected:
    ShaderManager *shaderManager;
    AGraphicsWrapper *graphicsWrapper;

protected:
    ColorRendererComponent(class ShaderManager *shaderManager, class AGraphicsWrapper *graphicsWrapper);

    virtual void onLoadShader(class Shader *shader);
    virtual void setupShaderVariables(class MeshComponent *mesh, class Shader *shader);
    virtual void preDraw();
    virtual void postDraw();

friend class Renderer;
};

} // namespace

#endif
