#include "Quaternion.h"

#include "math_util.h"

namespace sre
{

Quaternion::Quaternion()
{
	w = x = y = z = 0;
}

/*
	q = cos(angle/2) + axis * sin(angle/2)
*/
void Quaternion::setRotation(Vector axis, float angle)
{
	this->w = cosf(DEG2RAD(angle/2.0f));

	float sinAngle = sinf(DEG2RAD(angle/2.0f));
	this->x = axis.x * sinAngle;
	this->y = axis.y * sinAngle;
	this->z = axis.z * sinAngle;
}

/*
	1 - 2y^2 - 2z^2		2xy - 2wz			2xz + 2wy
	2xy + 2wz			1 - 2x^2 - 2z^2		2yz - 2wx
	2xz - 2wy			2yz + 2wx			1 - 2x^2 - 2y^2

	TRANSPOSED:
	1 - 2y^2 - 2z^2		2xy + 2wz			2xz - 2wy
	2xy - 2wz			1 - 2x^2 - 2z^2		2yz + 2wx
	2xz + 2wy			2yz - 2wx			1 - 2x^2 - 2y^2
*/
void Quaternion::getMatrix(float *matrix)
{
	matrix[0] = 1 - (2*y*y) - (2*z*z);
	matrix[1] = (2*x*y) - (2*w*z);
	matrix[2] = (2*x*z) + (2*w*y);

	matrix[4] = (2*x*y) + (2*w*z);
	matrix[5] = 1 - (2*x*x) - (2*z*z);
	matrix[6] = (2*y*z) - (2*w*x);

	matrix[8] = (2*x*z) - (2*w*y);
	matrix[9] = (2*y*z) + (2*w*x);
	matrix[10] = 1 - (2*x*x) - (2*y*y);
}

} // namespace