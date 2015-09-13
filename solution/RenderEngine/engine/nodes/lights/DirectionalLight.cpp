#include "DirectionalLight.h"

namespace nodes
{

DirectionalLight::DirectionalLight() : LightNode()
{
}

void DirectionalLight::setDirection(const Vector &direction)
{
    this->posDir = direction;
}

ELightType DirectionalLight::getType()
{
    return LIGHT_DIRECTIONAL;
}

} // namespace nodes
