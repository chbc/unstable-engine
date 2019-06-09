#include "LitRendererComponent.h"
#include "MeshComponent.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"

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
