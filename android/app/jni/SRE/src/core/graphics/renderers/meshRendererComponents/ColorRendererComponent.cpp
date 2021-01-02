#include "ColorRendererComponent.h"

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

void ColorRendererComponent::onSceneLoaded(class Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::MATERIAL_COLOR);
    this->shaderManager->setupAttributeLocation(shader, ShaderVariables::IN_POSITION);
}

void ColorRendererComponent::setupShaderValues(MeshComponent *mesh, Shader *shader)
{
    ColorMaterialComponent *colorMaterial = mesh->getMaterial()->getComponent<ColorMaterialComponent>();
    glm::vec4 color = colorMaterial->getColor();
    this->shaderManager->setVec4(shader, ShaderVariables::MATERIAL_COLOR, &color[0]);
}

void ColorRendererComponent::preDraw(Shader* shader)
{
    this->shaderManager->setVertexAttributePointer(shader, ShaderVariables::IN_POSITION, 3, sizeof(VertexData), VertexData::getPositionOffset());
}

void ColorRendererComponent::postDraw(Shader* shader)
{
    this->shaderManager->disableVertexAttribute(shader, ShaderVariables::IN_POSITION);
}

} // namespace
