#include "Material.h"
#include <engine/core/graphics/RenderManager.h>

namespace sre
{

Material::Material(float shininess)
{
	this->shininess = shininess;
	ColorMaterialComponent *component = this->addComponent<ColorMaterialComponent>();
}

void Material::setShininess(float shininess)
{
	this->shininess = shininess;
}

float Material::getShininess()
{
	return this->shininess;
}

} // namespace
