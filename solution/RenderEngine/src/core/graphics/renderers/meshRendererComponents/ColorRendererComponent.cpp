#include "ColorRendererComponent.h"
#include "ColorMaterialComponent.h"

#include "MeshComponent.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"

namespace sre
{

ColorRendererComponent::ColorRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
{
    this->shaderManager = shaderManager;
    this->graphicsWrapper = graphicsWrapper;
}

void ColorRendererComponent::onSceneLoaded(uint32_t program)
{
    this->shaderManager->setupUniformLocation(program, ShaderVariables::MATERIAL_COLOR);
    this->shaderManager->setupAttributeLocation(program, ShaderVariables::IN_POSITION);
}

void ColorRendererComponent::setupShaderValues(MeshComponent *mesh, uint32_t program)
{
    ColorMaterialComponent *colorMaterial = mesh->getMaterial()->getComponent<ColorMaterialComponent>();
    glm::vec4 color = colorMaterial->getColor();
    this->shaderManager->setVec4(program, ShaderVariables::MATERIAL_COLOR, &color[0]);
}

void ColorRendererComponent::preDraw(uint32_t program)
{
    this->graphicsWrapper->enableVertexPositions();
}

void ColorRendererComponent::postDraw(uint32_t program)
{
    this->shaderManager->disableVertexAttribute(program, ShaderVariables::IN_POSITION);
}

} // namespace
