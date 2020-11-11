#include "CameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace sre
{

CameraComponent::CameraComponent(Entity *entity) : AEntityComponent(entity)
{
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->lookAtTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    this->transform = this->getEntity()->getTransform();
    this->setPosition(glm::vec3(0.0f, 0.0f, 2.0f));

    this->view = glm::mat4(1.0f);
    this->projection = glm::mat4(1.0f);
}

void CameraComponent::setLookAt(const glm::vec3 &target)
{
    this->lookAtTarget = target;
}

void CameraComponent::setPosition(const glm::vec3 &position)
{
    this->transform->setPosition(position);
}

void CameraComponent::updateView()
{
    this->view = glm::lookAt(this->transform->getPosition(), this->lookAtTarget, this->up);
}

void CameraComponent::setProjection(float fov, float aspectRatio, float near, float far)
{
    this->projection = glm::perspective(fov, aspectRatio, near, far);
}

glm::mat4 CameraComponent::getViewMatrix()
{
    return this->view;
}

glm::mat4 CameraComponent::getProjectionMatrix()
{
    return this->projection;
}

} // namespace
