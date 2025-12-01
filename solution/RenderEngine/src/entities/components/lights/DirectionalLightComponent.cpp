#include "DirectionalLightComponent.h"
#include "TransformComponent.h"
#include "SingletonsManager.h"
#include "LightManager.h"

namespace sre
{

IMPLEMENT_COMPONENT(DirectionalLightComponent)

DirectionalLightComponent::DirectionalLightComponent(Entity *entity) : ALightComponent(entity)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	this->lightManager = singletonsManager->get<LightManager>();
	this->lightManager->addDirectionalLight(this);

	TransformComponent* transform = this->getTransform();
	this->propertyChangedCallbackId = transform->addPropertyChangedCallback
	(
		[this]()
		{
			this->lightManager->updateDirectionalLightsUBO();
			this->setupLightSpaceMatrix();
		}
	);
}

void DirectionalLightComponent::onPropertyChanged()
{
	AEntityComponent::onPropertyChanged();
	this->lightManager->updateDirectionalLightsUBO();
}

void DirectionalLightComponent::setupLightSpaceMatrix()
{
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f);
	TransformComponent* transform = this->getTransform();

	glm::vec3 position = glm::vec3(0.0f) - (transform->getForward() * 10.0f);
	glm::mat4 lightView = glm::lookAt
	(
		position,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	this->lightSpaceMatrix = lightProjection * lightView;
}

} // namespace
