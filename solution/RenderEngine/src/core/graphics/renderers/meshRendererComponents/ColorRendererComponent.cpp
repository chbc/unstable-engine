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
}

void ColorRendererComponent::setupShaderValues(MeshComponent *mesh, Shader *shader)
{
    ColorMaterialComponent *colorMaterial = mesh->getMaterial()->getComponent<ColorMaterialComponent>();
    glm::vec4 color = colorMaterial->getColor();
    this->shaderManager->setVec4(shader, ShaderVariables::MATERIAL_COLOR, &color[0]);
}

void ColorRendererComponent::preDraw()
{
    this->graphicsWrapper->enableVertexPositions();
}

void ColorRendererComponent::postDraw()
{
    this->graphicsWrapper->disableVertexPositions();
}

} // namespace
