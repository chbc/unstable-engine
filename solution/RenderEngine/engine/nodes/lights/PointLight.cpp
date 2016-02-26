#include "PointLight.h"

namespace sre
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

} // namespace
