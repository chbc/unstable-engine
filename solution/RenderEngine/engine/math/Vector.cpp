#include "Vector.h"

#include <cmath>
#include <engine/math/math_util.h>

const Vector Vector::ZERO(0.0f, 0.0f, 0.0f);
const Vector Vector::UP(0.0f, 1.0f, 0.0f);

// constructors //
Vector::Vector()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector::Vector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector Vector::operator +(const Vector &v)
{
	Vector result;
	result.x = this->x + v.x;
	result.y = this->y + v.y;
	result.z = this->z + v.z;

	return result;
}

Vector Vector::operator -(const Vector &v)
{
	Vector result;
	result.x = this->x - v.x;
	result.y = this->y - v.y;
	result.z = this->z - v.z;

	return result;
}

Vector Vector::operator *(float value)
{
	Vector result;
	result.x = this->x * value;
	result.y = this->y * value;
	result.z = this->z * value;

	return result;
}

// vector operations //
float Vector::magnitude()
{
	return sqrtf(powf(this->x, 2) + powf(this->y, 2) + powf(this->z, 2));
}

Vector Vector::normalize()
{
	Vector result;
	float magnitude = this->magnitude();

	if (magnitude > 0)
	{
		result.x = this->x / magnitude;
		result.y = this->y / magnitude;
		result.z = this->z / magnitude;
	}

	return result;
}

float Vector::dot(const Vector &v)
{
	float result = (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
	return result;
}

/*
|i	j	k |
|x	y	z |	=	|y	z |		-|x	 z |	+|x  y |	
|vx	vy	vz|		|vy	vz|		 |vx vz|	|vx vy|
*/
Vector Vector::cross(const Vector &v)
{
	Vector result;
	result.x =	(this->y * v.z) - (this->z * v.y);
	result.y = -((this->x * v.z) - (this->z * v.x));
	result.z =	(this->x * v.y) - (this->y * v.x);

	return result;
}

float Vector::distance(const Vector &v)
{
	Vector result = this->operator-(v);
	return result.magnitude();

	return -1;
}

/*
M(u, angle) = 
 __																																			  __	 __	  __
|	cos(angle) + (1 - cos(angle))u.x^2				u.x*u.y*(1 - cos(angle)) - u.z*sin(angle)		u.x*u.z*(1 - cos(angle)) + u.y*sin(angle)	|	|	x	|
|	u.y*u.x*(1 - cos(angle)) + u.z*sin(angle)		cos(angle) + u.y^2*(1 - cos(angle))				u.y*u.z*(1 - cos(angle)) - u.x*sin(angle)	|	|	y	|
|__	u.z*u.x*(1 - cos(angle)) - u.y*sin(angle)		u.z*u.y*(1 - cos(angle)) + u.x*sin(angle)		cos(angle) + u.z^2*(1 - cos(angle))		  __|	|__	z __|
*/
Vector Vector::rotate(const Vector &axis, float angle)
{
	Vector result;
	float rad = DEG2RAD(angle);
	float cosA = cosf(rad);
	float sinA = sinf(rad);
	float oneMinusCosA = 1 - cosA;

	result.x =	((cosA + (oneMinusCosA * axis.x * axis.x))				* this->x) +
				(((axis.x * axis.y * oneMinusCosA) - (axis.z * sinA))	* this->y) +
				(((axis.x * axis.z * oneMinusCosA) + (axis.y * sinA))	* this->z);

	result.y =	(((axis.y * axis.x * oneMinusCosA) + (axis.z * sinA))	* this->x) +
				((cosA + (axis.y * axis.y * oneMinusCosA))				* this->y) +
				(((axis.y * axis.z * oneMinusCosA) - (axis.x * sinA))	* this->z);

	result.z =	(((axis.z * axis.x * oneMinusCosA) - (axis.y * sinA))	* this->x) +
				(((axis.z * axis.y * oneMinusCosA) + (axis.x * sinA))	* this->y) +
				((cosA + (axis.z * axis.z * oneMinusCosA))				* this->z);

	return result;
}

void Vector::toArray(float *array)
{
	array[0] = this->x;
	array[1] = this->y;
	array[2] = this->z;
}
