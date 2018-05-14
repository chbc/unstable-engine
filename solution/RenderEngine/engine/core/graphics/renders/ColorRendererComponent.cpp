#include "ColorRendererComponent.h"

#include <engine/entities/components/meshes/MeshComponent.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>

namespace sre
{

ColorRendererComponent::ColorRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper)
{
    this->shaderManager = shaderManager;
    this->graphicsWrapper = graphicsWrapper;
}

void ColorRendererComponent::onLoadShader(class Shader *shader)
{
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::MATERIAL_COLOR);
    this->shaderManager->setupUniformLocation(shader, ShaderVariables::SHININESS);
}

void ColorRendererComponent::setupShaderVariables(MeshComponent *mesh, Shader *shader)
{
    ColorMaterialComponent *colorMaterial = mesh->getMaterial()->getComponent<ColorMaterialComponent>();
    glm::vec4 color = colorMaterial->getColor();
    this->shaderManager->setVec4(shader, ShaderVariables::MATERIAL_COLOR, &color[0]);
    this->shaderManager->setFloat(shader, ShaderVariables::SHININESS, mesh->getMaterial()->getShininess());
}

void ColorRendererComponent::preDraw()
{
    this->graphicsWrapper->enableVertexPositions();
    this->graphicsWrapper->enableVertexNormals();
}

void ColorRendererComponent::postDraw()
{
    this->graphicsWrapper->disableVertexPositions();
    this->graphicsWrapper->disableVertexNormals();
}

} // namespace
