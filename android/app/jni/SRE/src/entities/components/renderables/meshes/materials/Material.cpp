#include "Material.h"
#include "RenderManager.h"

namespace sre
{

Material::Material() : castShadow(true)
{
    this->addComponent<ColorMaterialComponent>();
    this->addComponent<LitMaterialComponent>();
}

void Material::setCastShadow(bool value)
{
	this->castShadow = value;
}

void Material::setReceivesLight(bool value)
{
    bool hasLit = this->hasComponent<LitMaterialComponent>();
    if (value && !hasLit)
        this->addComponent<LitMaterialComponent>();
    else if (!value && hasLit)
        this->removeComponent<LitMaterialComponent>();
}

bool Material::getReceivesLight()
{
    return this->hasComponent<LitMaterialComponent>();
}

} // namespace
