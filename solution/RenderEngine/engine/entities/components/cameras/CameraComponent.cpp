#include "CameraComponent.h"

namespace sre
{

CameraComponent::CameraComponent(Entity *entity) : AEntityComponent(entity)
{
    this->up = Vector(0.0f, 1.0f, 0.0f);
    this->lookAtTarget = Vector::ZERO;
}

void CameraComponent::setLookAt(const Vector &target)
{
	this->lookAtTarget = target;
}

} // namespace
