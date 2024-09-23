#include "CameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "SingletonsManager.h"
#include "EngineValues.h"
#include "Vec3EditorProperty.h"
#include "SingletonsManager.h"
#include "RenderManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace sre
{

IMPLEMENT_COMPONENT(CameraComponent)

CameraComponent::CameraComponent(Entity *entity) : AEntityComponent(entity)
{
    this->addEditorProperty(new Vec3EditorProperty{ "Look At Target", &this->lookAtTarget });
    this->addEditorProperty(new Vec3EditorProperty{ "Up", &this->up });

    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->lookAtTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    this->transform = this->getEntity()->getTransform();

    this->view = glm::mat4(1.0f);
    this->projection = glm::mat4(1.0f);

    setMainCamera();
}

void CameraComponent::setMainCamera()
{
    RenderManager* renderManager = SingletonsManager::getInstance()->resolve<RenderManager>();
    renderManager->setMainCamera(this);
}

void CameraComponent::setLookAt(const glm::vec3& target)
{
    this->lookAtTarget = target;
}

void CameraComponent::setPosition(const glm::vec3& position)
{
    this->transform->setPosition(position);
}

glm::vec3 CameraComponent::getPosition() const
{
    return this->transform->getPosition();
}

glm::vec3 CameraComponent::getLookAt() const
{
    return this->lookAtTarget;
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
