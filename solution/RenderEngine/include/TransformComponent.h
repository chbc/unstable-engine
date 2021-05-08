#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "AEntityComponent.h"
#include <glm/gtc/type_ptr.hpp>

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

private:
	TransformComponent(Entity *entity);

public:
	void setPosition(const glm::vec3 &position);
	void setScale(const glm::vec3 &scale);
	void setRotation(const glm::vec3 &axis, float angle);
	void setRotation(float* angles);

	void setLocalPosition(const glm::vec3 &position);
	void setLocalScale(const glm::vec3 &scale);
	void setLocalRotation(const glm::vec3 &axis, float angle);

	glm::vec3 getPosition();
	glm::quat getRotation();
	glm::vec3 getScale();
	glm::vec3 getLocalPosition();
	glm::quat getLocalRotation();
	glm::vec3 getLocalScale();

	void getPosition(float* result);
	void getRotation(float* result);
	void getScale(float* result);
	void getLocalPosition(float* result);
	void getLocalRotation(float* result);
	void getLocalScale(float* result);

	inline const glm::mat4 &getMatrix() { return this->worldMatrix; }

private:
	void propagateTransform();

friend class Entity;
};

} // namespace

#endif
