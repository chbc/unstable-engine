#include "ColorMaterial.h"
#include <engine/systems/graphics/RenderManager.h>

ColorMaterial::ColorMaterial() : Material()
{
    this->loadShader(shaderConsts::COLOR_V, shaderConsts::COLOR_F);
}

void ColorMaterial::apply(std::vector<VertexData> *vertexData, bool receiveLight)
{
    this->renderManager->applyMaterial(this, receiveLight);
}
