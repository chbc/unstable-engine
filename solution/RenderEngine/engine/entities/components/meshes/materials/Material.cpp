#include "Material.h"
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

Material::Material(float shininess)
{
	this->shininess = shininess;
	ColorMaterialComponent *component = this->addComponent<ColorMaterialComponent>();
	component->init();
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
