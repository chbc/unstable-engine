#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "Vector.h"

namespace sre
{

/*!
	Class to handle rotations
*/
class Quaternion
{
	private:
		float w, x, y, z;

	public:
		Quaternion();

		void setRotation(Vector axis, float angle);
		void getMatrix(float *matrix);
};

} // namespace

#endif
