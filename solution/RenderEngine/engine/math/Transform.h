#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Vector.h"
#include "Quaternion.h"

namespace sre
{

/*!
	Class used to apply transform operations to the scene nodes.
*/
class Transform
{
	private:
		Quaternion quaternion;
		float *matrix;

		void loadIdentity();

	public:
		Transform();
		~Transform();

		void setPosition(Vector position);
		void setScale(Vector scale);
		void setRotation(Vector axis, float angle);

		Vector getPosition();
		Quaternion getRotation();
		Vector getScale();

		inline float *getMatrix() { return this->matrix; }
};

} // namespace

#endif
