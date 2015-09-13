#include "PointLight.h"

namespace nodes
{

PointLight::PointLight() : LightNode()
{
}

void PointLight::setPosition(const Vector &position)
{
    this->posDir = position;
}

ELightType PointLight::getType()
{
    return LIGHT_POINT;
}

} // namespace nodes
