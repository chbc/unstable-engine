#include "CameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "SingletonsManager.h"
#include "EngineValues.h"
#include "XYZEditorProperty.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace sre
{

IMPLEMENT_COMPONENT(CameraComponent)

CameraComponent::CameraComponent(Entity *entity) : AEntityComponent(entity)
{
    this->addEditorProperty(new XYZEditorProperty{ "Look At Target", this->lookAtTarget });
    this->addEditorProperty(new XYZEditorProperty{ "Up", this->up });

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

const glm::vec3& CameraComponent::getPosition()
{
    return this->transform->getPosition();
}

void CameraComponent::updateView()
{
    this->view = glm::lookAt(this->transform->getPosition(), this->lookAtTarget, this->up);
}

void CameraComponent::setPerspectiveProjection(float fov, float aspectRatio, float near, float far)
{
    this->projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

void CameraComponent::setOrthoProjection()
{
    this->setOrthoProjection(static_cast<float>(EngineValues::SCREEN_WIDTH), static_cast<float>(EngineValues::SCREEN_HEIGHT));
}
 
void CameraComponent::setOrthoProjection(float width, float height)
{
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;
    this->projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.1f, 1000.0f);
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
