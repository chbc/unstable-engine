#include "TransformComponent.h"
#include "Entity.h"
#include "Vec3EditorProperty.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

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
TransformComponent::TransformComponent(Entity *entity) : AEntityComponent(entity),
	worldMatrix{1.0f}, localMatrix{1.0f}, position{0.0f}, eulerAngles{0.0f}, scale{1.0f}
{
	this->addEditorProperty(new Vec3EditorProperty{ "Position", &this->position });
	this->addEditorProperty(new Vec3EditorProperty{ "Rotation", &this->eulerAngles });
	this->addEditorProperty(new Vec3EditorProperty{ "Scale", &this->scale, 1.0f });
}

void TransformComponent::setPosition(const glm::vec3& arg_position)
{
	this->position = arg_position;

	this->updateMatrix();
}

void TransformComponent::setScale(const glm::vec3& arg_scale)
{
	this->scale = arg_scale;

	this->updateMatrix();
}

void TransformComponent::setRotation(const glm::vec3& axis, float angle)
{
	glm::mat4 rotationMatrix{ 1.0f };

	rotationMatrix = glm::rotate(rotationMatrix, angle, axis);
	rotationMatrix = glm::transpose(rotationMatrix);

	glm::quat quaternion;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::vec3 decomposedScale;
	glm::vec3 decomposedPosition;
	glm::decompose(rotationMatrix, decomposedScale, quaternion, decomposedScale, skew, perspective);

	this->eulerAngles.x = glm::degrees(glm::pitch(quaternion));
	this->eulerAngles.y = glm::degrees(glm::yaw(quaternion));
	this->eulerAngles.z = glm::degrees(glm::roll(quaternion));

	this->updateMatrix();
}

void TransformComponent::setRotation(glm::vec3 arg_eulerAngles)
{
	this->eulerAngles = arg_eulerAngles;

	this->updateMatrix();
}

glm::vec3 TransformComponent::getPosition() const
{
	return this->position;
}

glm::vec3 TransformComponent::getRotation()
{
	return this->eulerAngles;
}

glm::vec3 TransformComponent::getScale()
{
	return this->scale;
}

void TransformComponent::getPosition(float* result)
{
	result[0] = this->position.x;
	result[1] = this->position.y;
	result[2] = this->position.z;
}

void TransformComponent::getRotation(float* result)
{
	result[0] = eulerAngles.x;
	result[1] = eulerAngles.y;
	result[2] = eulerAngles.z;
}

void TransformComponent::getScale(float* result)
{
	result[0] = this->scale.x;
	result[1] = this->scale.y;
	result[2] = this->scale.z;
}

/*
void TransformComponent::setLocalPosition(const glm::vec3& arg_position)
{
	this->localMatrix[3][0] = position.x;
	this->localMatrix[3][1] = position.y;
	this->localMatrix[3][2] = position.z;

	this->worldMatrix *= this->localMatrix;

	this->propagateTransform();
}

void TransformComponent::setLocalScale(const glm::vec3& arg_scale)
{
	this->localMatrix[0] = this->localMatrix[0] * scale[0];
	this->localMatrix[1] = this->localMatrix[1] * scale[1];
	this->localMatrix[2] = this->localMatrix[2] * scale[2];

	this->worldMatrix *= this->localMatrix;

	this->setDirty();
	this->propagateTransform();
}

void TransformComponent::setLocalRotation(const glm::vec3 &axis, float angle)
{
	glm::mat4 rotationMatrix;
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), axis);
	this->localMatrix *= glm::transpose(rotationMatrix);
	this->worldMatrix *= this->localMatrix;

	this->setDirty();
	this->propagateTransform();
}

glm::vec3 TransformComponent::getLocalPosition() const
{
	return glm::vec3(this->localMatrix[3][0], this->localMatrix[3][1], this->localMatrix[3][2]);
}

glm::quat TransformComponent::getLocalRotation()
{
	return glm::quat_cast(this->localMatrix);
}

glm::vec3 TransformComponent::getLocalScale()
{
	return glm::vec3(this->localMatrix[0][0], this->localMatrix[1][1], this->localMatrix[2][2]); // XXX
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
*/

glm::vec3 TransformComponent::getForwardVector()
{
	return glm::vec3{ 0.0f };
}

glm::vec3 TransformComponent::getRightVector()
{
	return glm::vec3{ 0.0f };
}

void TransformComponent::onValueChanged()
{
	this->updateMatrix();
}

void TransformComponent::updateMatrix()
{
	glm::mat4 transformMatrix{ 1.0f };

	transformMatrix = glm::translate(transformMatrix, this->position);
	transformMatrix = glm::rotate(transformMatrix, glm::radians(this->eulerAngles.x), glm::vec3{ 1.0f, 0.0f, 0.0f });
	transformMatrix = glm::rotate(transformMatrix, glm::radians(this->eulerAngles.y), glm::vec3{ 0.0f, 1.0f, 0.0f });
	transformMatrix = glm::rotate(transformMatrix, glm::radians(this->eulerAngles.z), glm::vec3{ 0.0f, 0.0f, 1.0f });
	this->worldMatrix = glm::scale(transformMatrix, this->scale);

	/*
	this->rotationMatrix = glm::eulerAngleXYZ(
		glm::radians(this->eulerAngles.x), glm::radians(this->eulerAngles.y), glm::radians(this->eulerAngles.z)
	);
	this->rotationMatrix *= glm::transpose(rotationMatrix);
	*/

	this->localMatrix = this->worldMatrix; // XXX

	this->propagateTransform();
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
