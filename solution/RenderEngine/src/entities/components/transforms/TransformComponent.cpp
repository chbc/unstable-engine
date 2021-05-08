#include "TransformComponent.h"
#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace sre
{

IMPLEMENT_COMPONENT(TransformComponent)

/*
	Matrix Format
	00	10	20	30
	01	11	21	31
	02	12	22	32
	t1	t2	t3	33
*/
TransformComponent::TransformComponent(Entity *entity) : AEntityComponent(entity)
{
}

void TransformComponent::setPosition(const glm::vec3 &position)
{
	this->worldMatrix[3][0] = position.x;
	this->worldMatrix[3][1] = position.y;
	this->worldMatrix[3][2] = position.z;

	this->localMatrix = this->worldMatrix; // ###

	this->propagateTransform();
}

void TransformComponent::setScale(const glm::vec3 &scale)
{
	this->worldMatrix[0][0] = scale.x;
	this->worldMatrix[1][1] = scale.y;
	this->worldMatrix[2][2] = scale.z;

	this->localMatrix = this->worldMatrix; // ###

	this->propagateTransform();
}

void TransformComponent::setRotation(const glm::vec3 &axis, float angle)
{
	glm::mat4 rotationMatrix;

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), axis);
	this->worldMatrix *= glm::transpose(rotationMatrix);
	
	this->localMatrix = this->worldMatrix; // ###

	this->propagateTransform();
}

void TransformComponent::setRotation(float* angles)
{
	glm::mat4 rotationMatrix;

	rotationMatrix = glm::eulerAngleXYZ(glm::radians(angles[0]), glm::radians(angles[1]), glm::radians(angles[2]));
	this->worldMatrix *= glm::transpose(rotationMatrix);

	this->localMatrix = this->worldMatrix; // ###

	this->propagateTransform();
}

void TransformComponent::setLocalPosition(const glm::vec3 &position)
{
	this->localMatrix[3][0] = position.x;
	this->localMatrix[3][1] = position.y;
	this->localMatrix[3][2] = position.z;

	this->worldMatrix *= this->localMatrix;

	this->propagateTransform();
}

void TransformComponent::setLocalScale(const glm::vec3 &scale)
{
	this->localMatrix[0][0] = scale.x;
	this->localMatrix[1][1] = scale.y;
	this->localMatrix[2][2] = scale.z;

	this->worldMatrix *= this->localMatrix;

	this->propagateTransform();
}

void TransformComponent::setLocalRotation(const glm::vec3 &axis, float angle)
{
	glm::mat4 rotationMatrix;
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), axis);
	this->localMatrix *= glm::transpose(rotationMatrix);

	this->worldMatrix *= this->localMatrix;

	this->propagateTransform();
}

glm::vec3 TransformComponent::getPosition()
{
	return glm::vec3(this->worldMatrix[3][0], this->worldMatrix[3][1], this->worldMatrix[3][2]);
}

glm::quat TransformComponent::getRotation()
{
	return glm::quat_cast(this->worldMatrix);
}

glm::vec3 TransformComponent::getScale()
{
	return glm::vec3(this->worldMatrix[0][0], this->worldMatrix[1][1], this->worldMatrix[2][2]);
}

glm::vec3 TransformComponent::getLocalPosition()
{
	return glm::vec3(this->localMatrix[3][0], this->localMatrix[3][1], this->localMatrix[3][2]);
}

glm::quat TransformComponent::getLocalRotation()
{
	return glm::quat_cast(this->localMatrix);
}

glm::vec3 TransformComponent::getLocalScale()
{
	return glm::vec3(this->localMatrix[0][0], this->localMatrix[1][1], this->localMatrix[2][2]);
}

void TransformComponent::getPosition(float* result)
{
	result[0] = this->worldMatrix[3][0];
	result[1] = this->worldMatrix[3][1];
	result[2] = this->worldMatrix[3][2];
}

void TransformComponent::getRotation(float* result)
{
	glm::quat quaternion = glm::quat_cast(this->worldMatrix);
	glm::vec3 angles = glm::eulerAngles(quaternion);

	result[0] = angles.x;
	result[1] = angles.y;
	result[2] = angles.z;
}

void TransformComponent::getScale(float* result)
{
	result[0] = this->worldMatrix[0][0];
	result[1] = this->worldMatrix[1][1];
	result[2] = this->worldMatrix[2][2];
}

void TransformComponent::getLocalPosition(float* result)
{
	result[0] = this->localMatrix[3][0];
	result[1] = this->localMatrix[3][1];
	result[2] = this->localMatrix[3][2];
}

void TransformComponent::getLocalRotation(float* result)
{
	glm::quat quaternion = glm::quat_cast(this->localMatrix);
	glm::vec3 angles = glm::eulerAngles(quaternion);

	result[0] = angles.x;
	result[1] = angles.y;
	result[2] = angles.z;
}

void TransformComponent::getLocalScale(float* result)
{
	result[0] = this->localMatrix[0][0];
	result[1] = this->localMatrix[1][1];
	result[2] = this->localMatrix[2][2];
}

void TransformComponent::propagateTransform()
{
	Entity *entity = this->getEntity();
	uint32_t size = entity->getChildrenCount();
	for (uint32_t i = 0; i < size; i++)
	{
		Entity *child = entity->getChild(i);
		TransformComponent *childTransform = child->getComponent<TransformComponent>();
		childTransform->worldMatrix = this->worldMatrix * childTransform->localMatrix;
		childTransform->propagateTransform();
	}
}

} // namespace
