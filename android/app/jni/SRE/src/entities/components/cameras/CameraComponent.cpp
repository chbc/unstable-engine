#include "CameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

namespace sre
{

CameraComponent::CameraComponent(Entity *entity) : AEntityComponent(entity)
{
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->lookAtTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    this->transform = this->getEntity()->getTransform();
    this->setPosition(glm::vec3(0.0f, 0.0f, 2.0f));
}

void CameraComponent::setLookAt(const glm::vec3 &target)
{
    this->lookAtTarget = target;
}

void CameraComponent::setPosition(const glm::vec3 &position)
{
    this->transform->setPosition(position);
}

} // namespace
