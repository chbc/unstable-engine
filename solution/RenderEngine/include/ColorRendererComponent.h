#pragma once

#include <cstdint>

// ### TRANSFORMAR OS COMPONENTES EM INSTÂNCIA ÚNICA
// ### RENOMEAR PRA REFERENCIAR OS MESHES
namespace sre
{

class ShaderManager;
class AGraphicsWrapper;

class ColorRendererComponent
{
protected:
    ShaderManager* shaderManager;
    AGraphicsWrapper* graphicsWrapper;

public:
    virtual ~ColorRendererComponent() = default;
	
protected:
    ColorRendererComponent(ShaderManager* shaderManager, class AGraphicsWrapper* graphicsWrapper);

    virtual void onSceneLoaded(uint32_t program);
    virtual void setupShaderValues(class MeshComponent* mesh, uint32_t program);
    virtual void preDraw(uint32_t program);
    virtual void postDraw(uint32_t program);

friend class MeshRenderer;
};

} // namespace
