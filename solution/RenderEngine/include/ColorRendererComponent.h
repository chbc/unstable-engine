#ifndef _COLOR_RENDERER_COMPONENT_H_
#define _COLOR_RENDERER_COMPONENT_H_

// ### TRANSFORMAR OS COMPONENTES EM INST�NCIA �NICA
// ### RENOMEAR PRA REFERENCIAR OS MESHES
namespace sre
{

class ShaderManager;
class AGraphicsWrapper;
class Shader;

class ColorRendererComponent
{
protected:
    ShaderManager* shaderManager;
    AGraphicsWrapper* graphicsWrapper;

public:
    virtual ~ColorRendererComponent() = default;
	
protected:
    ColorRendererComponent(ShaderManager* shaderManager, class AGraphicsWrapper* graphicsWrapper);

    virtual void onSceneLoaded(Shader* shader);
    virtual void setupShaderValues(class MeshComponent* mesh, Shader* shader);
    virtual void preDraw(Shader* shader);
    virtual void postDraw(Shader* shader);

friend class MeshRenderer;
};

} // namespace

#endif
