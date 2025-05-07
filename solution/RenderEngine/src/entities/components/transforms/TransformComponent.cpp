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
	glm::mat4 identity;
	this->rotation = glm::rotate(identity, glm::radians(angle), axis);
	this->updateMatrix();
}

void TransformComponent::rotate(const glm::vec3& axis, float angle)
{
	this->rotation = glm::rotate(this->rotation, glm::radians(angle), axis);
	this->updateMatrix();
}

void TransformComponent::rotate(glm::vec3 arg_eulerAngles)
{
	this->eulerAngles += arg_eulerAngles;
	this->updateMatrix();
}

glm::vec3 TransformComponent::getPosition() const
{
	return this->position;
}

glm::quat TransformComponent::getRotation() const
{
	return glm::quat{ this->rotation };
}

glm::vec3 TransformComponent::getScale() const
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

const glm::vec3 TransformComponent::getInternalMatrixPosition() const
{
	return glm::vec3(this->worldMatrix[3]);
}

glm::vec3 TransformComponent::getForward() const
{
	glm::vec3 result{ this->worldMatrix[2].x, this->worldMatrix[2].y, this->worldMatrix[2].z };
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

void TransformComponent::onPropertyDeserialized()
{
	AEntityComponent::onPropertyDeserialized();

	glm::quat quaternionRotation = glm::quat{ glm::radians(this->eulerAngles) };
	this->rotation = glm::toMat4(quaternionRotation);
	this->updateMatrix();
}

void TransformComponent::onPropertyChanged()
{
	AEntityComponent::onPropertyChanged();
	this->onPropertyDeserialized();
}

void TransformComponent::updateMatrix()
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4{ 1.0 }, this->position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4{ 1.0f }, this->scale);
	glm::mat4 rotationMatrix = this->rotation;

	this->worldMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	this->localMatrix = this->worldMatrix; // XXX

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
		childTransform->worldMatrix = this->worldMatrix * childTransform->localMatrix;
		childTransform->propagateTransform();
	}
}

} // namespace
