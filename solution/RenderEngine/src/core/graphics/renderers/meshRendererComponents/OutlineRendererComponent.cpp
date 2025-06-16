#include "OutlineRendererComponent.h"

#include "MeshComponent.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"

namespace sre
{

OutlineRendererComponent::OutlineRendererComponent(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper)
	: ColorRendererComponent(shaderManager, graphicsWrapper)
{ }

void OutlineRendererComponent::onSceneLoaded(uint32_t program)
{
    // XXX this->shaderManager->setupUniformLocation(shader, ShaderVariables::OUTLINE_COLOR);
}

void OutlineRendererComponent::setupShaderValues(MeshComponent* mesh, uint32_t program)
{
}

void OutlineRendererComponent::preDraw(uint32_t program)
{
    this->graphicsWrapper->enableVertexPositions();
}

void OutlineRendererComponent::postDraw(uint32_t program)
{
    this->graphicsWrapper->disableVertexPositions();
}

} // namespace
