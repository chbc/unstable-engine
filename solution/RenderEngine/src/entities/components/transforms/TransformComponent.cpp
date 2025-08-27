#include "TransformComponent.h"
#include "Entity.h"
#include "Vec3EditorProperty.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

namespace sre
{

IMPLEMENT_COMPONENT(TransformComponent)

glm::vec3 TransformComponent::ZERO{ 0.0f, 0.0f, 0.0f };
glm::vec3 TransformComponent::RIGHT{ 1.0f, 0.0f, 0.0f };
glm::vec3 TransformComponent::UP{ 0.0f, 1.0f, 0.0f };
glm::vec3 TransformComponent::FRONT{ 0.0f, 0.0f, 1.0f };

/*
	Matrix Format
	00	10	20	30
	01	11	21	31
	02	12	22	32
	t1	t2	t3	33
*/
TransformComponent::TransformComponent(Entity *entity) : AEntityComponent(entity)
{
	this->addEditorProperty(new Vec3EditorProperty{ "Position", &this->position });
	this->addEditorProperty(new Vec3EditorProperty{ "Rotation", &this->eulerAngles });
	this->addEditorProperty(new Vec3EditorProperty{ "Scale", &this->scale, 1.0f });
}

void TransformComponent::setPosition(glm::vec3 arg_position)
{
	this->position = arg_position;
	this->updateMatrix();
}

void TransformComponent::translate(const glm::vec3& translation)
{
	this->position += translation;
	this->updateMatrix();
}

void TransformComponent::setScale(glm::vec3 arg_scale)
{
	this->scale = arg_scale;
	this->updateMatrix();
}

void TransformComponent::setRotation(const glm::vec3& axis, float angle)
{
	glm::mat4 identity{ 1.0f };
	this->rotation = glm::rotate(identity, glm::radians(angle), axis);
	this->updateMatrix();
}

void TransformComponent::setRotation(const glm::vec3& arg_eulerAngles)
{
	this->eulerAngles = arg_eulerAngles;
	glm::quat quaternionRotation = glm::quat{ glm::radians(arg_eulerAngles) };
	this->rotation = glm::toMat4(quaternionRotation);

	this->updateMatrix();
}

void TransformComponent::setRotation(const glm::quat& arg_rotation)
{
	this->rotation = glm::toMat4(arg_rotation);
	this->updateMatrix();
}

void TransformComponent::setLookAtRotation(const glm::vec3& targetPosition)
{
	this->rotation = glm::mat4{ 1.0f };
	glm::vec3 direction = glm::normalize(targetPosition - this->getPosition());
	glm::vec3 right = glm::cross(direction, UP);
	if (glm::length(right) < 0.0001f)
	{
		right = glm::cross(direction, FRONT);
	}

	glm::vec3 up = glm::cross(right, direction);
	this->rotation[0] = glm::vec4{ right, 0.0f };
	this->rotation[1] = glm::vec4{ up, 0.0f };
	this->rotation[2] = glm::vec4{ -direction, 0.0f };

	this->updateMatrix();
}

void TransformComponent::rotate(const glm::vec3& axis, float angle)
{
	this->rotation = glm::rotate(this->rotation, glm::radians(-angle), axis);
	this->updateMatrix();
}

void TransformComponent::rotate(glm::vec3 arg_eulerAngles)
{
	this->eulerAngles += arg_eulerAngles;
	this->updateMatrix();
}

glm::vec3 TransformComponent::getPosition() const
{
	return glm::vec3(this->worldMatrix[3]);
}

glm::quat TransformComponent::getRotation() const
{
	glm::mat4 result = this->parentMatrix * this->rotation;
	return glm::quat{ result };
}

void TransformComponent::getRotation(float& pitch, float& yaw, float& roll) const
{
	glm::vec3 forward = this->getForward();
	pitch = glm::atan(forward.y, glm::sqrt((forward.x * forward.x) + (forward.z * forward.z)));
	yaw = glm::atan(forward.x, forward.z);

	glm::vec3 up = this->getUp();
	roll = glm::atan(up.x, up.y);

	pitch = glm::degrees(pitch);
	yaw = glm::degrees(yaw);
	roll = glm::degrees(roll);
}

glm::vec3 TransformComponent::getScale() const
{
	glm::vec4 result = this->parentMatrix * glm::vec4{ this->scale, 1.0f };
	return glm::vec3{ result };
}

glm::vec3 TransformComponent::getLocalPosition() const
{
	return this->position;
}

glm::quat TransformComponent::getLocalRotation() const
{
	return glm::quat{ this->rotation };
}

glm::vec3 TransformComponent::getLocalScale() const
{
	return this->scale;
}

const glm::vec3 TransformComponent::getInternalMatrixPosition() const
{
	return glm::vec3(this->worldMatrix[3]);
}

glm::vec3 TransformComponent::getForward() const
{
	glm::vec3 result{ this->worldMatrix[2] };
	return glm::normalize(result);
}

glm::vec3 TransformComponent::getRight() const
{
	glm::vec3 result{ this->worldMatrix[0].x, this->worldMatrix[0].y, this->worldMatrix[0].z };
	return glm::normalize(result);
}

inline glm::vec3 TransformComponent::getUp() const
{
	glm::vec3 result{ glm::vec3{this->worldMatrix[1]} };
	return glm::normalize(result);
}

inline const glm::mat4& TransformComponent::getMatrix() const
{
	return this->worldMatrix;
}

void TransformComponent::getValues(TransformComponent* resultTransform) const
{
	resultTransform->rotation = this->rotation;
	resultTransform->position = this->position;
	resultTransform->eulerAngles = this->eulerAngles;
	resultTransform->scale = this->scale;
	resultTransform->parentMatrix = this->parentMatrix;
	resultTransform->updateMatrix();
}

void TransformComponent::onPropertyDeserialized()
{
	AEntityComponent::onPropertyDeserialized();

	glm::quat quaternionRotation = glm::quat{ glm::radians(this->eulerAngles) };
	this->rotation = glm::toMat4(quaternionRotation);
	this->updateMatrix();
}

void TransformComponent::onPropertyChanged()
{
	this->onPropertyDeserialized();
	AEntityComponent::onPropertyChanged();
}

void TransformComponent::updateMatrix()
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4{ 1.0 }, this->position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4{ 1.0f }, this->scale);

	glm::mat4 localMatrix = translationMatrix * this->rotation * scaleMatrix;
	this->worldMatrix = this->parentMatrix * localMatrix;

	this->propagateTransform();
}

void TransformComponent::propagateTransform()
{
	Entity *entity = this->getEntity();
	size_t size = entity->getChildrenCount();
	for (uint32_t i = 0; i < size; i++)
	{
		Entity *child = entity->getChild(i);
		TransformComponent *childTransform = child->getComponent<TransformComponent>();
		childTransform->parentMatrix = this->worldMatrix;
		childTransform->updateMatrix();
	}
}

} // namespace
