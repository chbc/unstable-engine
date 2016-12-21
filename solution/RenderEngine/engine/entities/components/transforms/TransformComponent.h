#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <engine/entities/components/AEntityComponent.h>
#include <glm/vec3.hpp>
#include <engine/math/Quaternion.h>

namespace sre
{

/*!
	Class used to apply transform operations to the entities.
*/
class TransformComponent : public AEntityComponent
{
private:
	Quaternion quaternion;
	float *matrix;

	void loadIdentity();

	TransformComponent(Entity *entity);
public:
	~TransformComponent();

	void setPosition(const glm::vec3 &position);
	void setScale(const glm::vec3 &scale);
	void setRotation(const glm::vec3 &axis, float angle);

	glm::vec3 getPosition();
	Quaternion getRotation();
	glm::vec3 getScale();

	inline float *getMatrix() { return this->matrix; }

friend class Entity;
};

} // namespace

#endif
