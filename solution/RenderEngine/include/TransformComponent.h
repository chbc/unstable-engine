#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "AEntityComponent.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/detail/type_mat.hpp>

namespace sre
{

class Entity;

/*!
	Class used to apply transform operations to the entities.
*/
class SRE_API TransformComponent : public AEntityComponent
{
DECLARE_COMPONENT()

private:
	glm::mat4 worldMatrix;
	glm::mat4 localMatrix;

	glm::vec3 position;
	glm::vec3 eulerAngles;
	glm::vec3 scale;

public:
	TransformComponent(Entity *entity);
	void setPosition(const glm::vec3& arg_position);
	void setScale(const glm::vec3& arg_scale);
	void setRotation(const glm::vec3& axis, float angle);
	void setRotation(glm::vec3 arg_eulerAngles);
	glm::vec3 getPosition() const;
	glm::vec3 getRotation();
	glm::vec3 getScale();
	void getPosition(float* result);
	void getRotation(float* result);
	void getScale(float* result);

	/*
	void setLocalPosition(const glm::vec3& arg_position);
	void setLocalScale(const glm::vec3& arg_scale);
	void setLocalRotation(const glm::vec3& axis, float angle);
	glm::vec3 getLocalPosition() const;
	glm::quat getLocalRotation();
	glm::vec3 getLocalScale();
	void getLocalPosition(float* result);
	void getLocalRotation(float* result);
	void getLocalScale(float* result);
	*/
	glm::vec3 getForwardVector();
	glm::vec3 getRightVector();

	inline const glm::mat4 &getMatrix() { return this->worldMatrix; }

protected:
	void onValueChanged() override;

private:
	void updateMatrix();
	void propagateTransform();

friend class Entity;
friend class TransformEditorProperty;
};

} // namespace

#endif
