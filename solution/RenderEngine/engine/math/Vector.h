#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <glm/vec3.hpp>

namespace sre
{

/*!
	Class to deal with vector operations.
*/
class Vector
{
	public:
		float x, y, z;

		const static Vector ZERO;
		const static Vector UP;

		Vector();
		Vector(float x, float y, float z = 0.0f);

		Vector operator +(const Vector &v);
		Vector operator -(const Vector &v);
		Vector operator *(float value);

		float magnitude();
		float length();
		Vector normalize();
		float dot(const Vector &v);
		Vector cross(const Vector &v);
		float distance(const Vector &v);
		Vector rotate(const Vector &axis, float angle);

		void toArray(float *array);
		glm::vec3 toVec3();
};

} // namespace
#endif
