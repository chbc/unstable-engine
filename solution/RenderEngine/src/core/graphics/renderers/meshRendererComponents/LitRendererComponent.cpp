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

void LitRendererComponent::onSceneLoaded(uint32_t program)
{
    this->state->onSceneLoaded(this->shaderManager, program);
}

void LitRendererComponent::setupShaderValues(MeshComponent *mesh, uint32_t program)
{
    this->state->setupShaderValues(this->shaderManager, mesh, program);
}

void LitRendererComponent::preDraw(uint32_t program)
{
    this->state->preDraw(this->graphicsWrapper);
}

void LitRendererComponent::postDraw(uint32_t program)
{
    this->state->postDraw(this->graphicsWrapper);
}

} // namespace
