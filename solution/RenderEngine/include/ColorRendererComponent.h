#ifndef _COLOR_RENDERER_COMPONENT_H_
#define _COLOR_RENDERER_COMPONENT_H_

// ### TRANSFORMAR OS COMPONENTES EM INSTÂNCIA ÚNICA
// ### RENOMEAR PRA REFERENCIAR OS MESHES
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

    virtual void onSceneLoaded(Shader *shader);
    virtual void setupShaderValues(class MeshComponent *mesh, Shader *shader);
    virtual void preDraw();
    virtual void postDraw();

friend class MeshRenderer;
};

} // namespace

#endif
