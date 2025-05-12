#include "CameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "SingletonsManager.h"
#include "EngineValues.h"
#include "Vec3EditorProperty.h"
#include "BoolEditorProperty.h"
#include "FloatEditorProperty.h"
#include "RenderManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace sre
{

IMPLEMENT_COMPONENT(CameraComponent)

CameraComponent::CameraComponent(Entity *entity) : AEntityComponent(entity),
    projection(1.0f), isPerspective(true), fov(90.0f), orthoWidth(1.0f),
    orthoHeight(1.0f), isMainCamera(false), isApplicationCamera(true)
{
    this->addEditorProperty(new BoolEditorProperty{ "Perspective", &this->isPerspective });
    this->addEditorProperty(new BoolEditorProperty{ "Main Camera", &this->isMainCamera });
    this->addEditorProperty(new FloatEditorProperty{ "FOV", &this->fov });

    this->transform = this->getEntity()->getTransform();
    this->projection = glm::mat4(1.0f);
}

void CameraComponent::setPerspectiveProjection(float arg_fov, float aspectRatio, float near, float far)
{
    this->isPerspective = true;
    this->fov = arg_fov;
    this->projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

void CameraComponent::setOrthoProjection()
{
    this->setOrthoProjection(static_cast<float>(EngineValues::SCREEN_WIDTH), static_cast<float>(EngineValues::SCREEN_HEIGHT));
}
 
void CameraComponent::setOrthoProjection(float width, float height)
{
    this->isPerspective = false;
    this->orthoWidth = width;
    this->orthoHeight = height;
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;
    this->projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.1f, 1000.0f);
}

void CameraComponent::setMainCamera()
{
    this->isMainCamera = true;
    RenderManager* renderManager = SingletonsManager::getInstance()->get<RenderManager>();
    renderManager->setApplicationCamera(this);
}

void CameraComponent::updateView()
{
    this->view = glm::inverse(this->transform->getMatrix());
}

const glm::mat4& CameraComponent::getProjectionMatrix() const
{
    return this->projection;
}

const glm::mat4& CameraComponent::getViewMatrix() const
{
    return this->view;
}

void CameraComponent::onPropertyDeserialized()
{
    AEntityComponent::onPropertyDeserialized();
    if (this->isPerspective)
    {
        this->setPerspectiveProjection(this->fov, EngineValues::ASPECT_RATIO, 0.1f, 1000.0f);
    }
    else
    {
        this->setOrthoProjection();
    }

    if (this->isMainCamera)
    {
        this->setMainCamera();
    }
}

void CameraComponent::onPropertyChanged()
{
    AEntityComponent::onPropertyChanged();
    this->onPropertyDeserialized();
}

} // namespace
