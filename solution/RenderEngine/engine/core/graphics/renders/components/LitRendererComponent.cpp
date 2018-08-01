#include "LitRendererComponent.h"
#include <engine/entities/components/renderables/meshes/MeshComponent.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

LitRendererComponent::LitRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper, bool hasLight)
    : ColorRendererComponent(shaderManager, graphicsWrapper)
{
    this->state = UPTR<LitRendererNoLightsState>
    (
        hasLight ? new LitRendererLightsState{} : new LitRendererNoLightsState{}
    );
}

void LitRendererComponent::onSceneLoaded(Shader *shader)
{
    this->state->onSceneLoaded(this->shaderManager, shader);
}

void LitRendererComponent::setupShaderValues(MeshComponent *mesh, Shader *shader)
{
    this->state->setupShaderValues(this->shaderManager, mesh, shader);
}

void LitRendererComponent::preDraw()
{
    this->state->preDraw(this->graphicsWrapper);
}

void LitRendererComponent::postDraw()
{
    this->state->postDraw(this->graphicsWrapper);
}

} // namespace
