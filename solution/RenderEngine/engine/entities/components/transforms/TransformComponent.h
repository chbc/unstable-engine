#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <engine/entities/components/AEntityComponent.h>
#include <engine/math/Vector.h>
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

	void setPosition(Vector position);
	void setScale(Vector scale);
	void setRotation(Vector axis, float angle);

	Vector getPosition();
	Quaternion getRotation();
	Vector getScale();

	inline float *getMatrix() { return this->matrix; }

friend class Entity;
};

} // namespace

#endif
