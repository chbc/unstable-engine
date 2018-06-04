#ifndef _COLOR_RENDERER_COMPONENT_H_
#define _COLOR_RENDERER_COMPONENT_H_

#include <stdint.h>

// ### TRANSFORMAR OS COMPONENTES EM SINGLETONS
namespace sre
{

class ShaderManager;
class AGraphicsWrapper;
class Shader;

class ColorRendererComponent
{
protected:
    ShaderManager *shaderManager;
    AGraphicsWrapper *graphicsWrapper;

protected:
    ColorRendererComponent(ShaderManager *shaderManager, class AGraphicsWrapper *graphicsWrapper);

    virtual void onLoadShader(Shader *shader);
    virtual void setupShaderVariables(class MeshComponent *mesh, Shader *shader);
    virtual void preDraw();
    virtual void postDraw();

friend class Renderer;
};

} // namespace

#endif
