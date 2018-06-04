#include "Material.h"
#include <engine/core/graphics/RenderManager.h>

namespace sre
{

Material::Material(bool arg_receivesLight, float arg_shininess)
    : receivesLight(arg_receivesLight), shininess(arg_shininess)
{
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
