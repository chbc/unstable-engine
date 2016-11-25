#include "ColorMaterialComponent.h"
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

ColorMaterialComponent::ColorMaterialComponent() : AMaterialComponent()
{
    // ### this->loadShader(shaderConsts::COLOR_V, shaderConsts::COLOR_F);

	this->ambient = glm::vec3{ 0.3f };
	this->diffuse = glm::vec3{ 0.7f };
	this->specular = glm::vec3{ 0.9f };
}

/* ###
void ColorMaterial::apply(std::vector<VertexData> *vertexData, bool receiveLight)
{
    this->renderManager->applyMaterial(this, receiveLight);
}
*/

void ColorMaterialComponent::setAmbient(const glm::vec3 &ambient)
{
	this->ambient = ambient;
}

void ColorMaterialComponent::setDiffuse(const glm::vec3 &diffuse)
{
	this->diffuse = diffuse;
}
	
void ColorMaterialComponent::setSpecular(const glm::vec3 &specular)
{
	this->specular = specular;
}

} // namespace
