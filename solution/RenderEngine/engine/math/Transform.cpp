#include "Transform.h"

namespace sre
{

/*
	Matrix Format
	0	4	8	12
	1	5	9	13
	2	6	10	14
	3	7	11	15
*/
Transform::Transform()
{
	this->matrix = new float[16];
	this->loadIdentity();
}

Transform::~Transform()
{
	delete this->matrix;
}

void Transform::loadIdentity()
{
	for (int i = 0; i < 16; i++)
	{
		if ((i == 0) || (i == 5) || (i == 10) || (i == 15))
			this->matrix[i] = 1;
		else
			this->matrix[i] = 0;
	}
}

void Transform::setPosition(Vector position)
{
	this->matrix[12] = position.x;
	this->matrix[13] = position.y;
	this->matrix[14] = position.z;
}

void Transform::setScale(Vector scale)
{
	this->matrix[0] = scale.x;
	this->matrix[5] = scale.y;
	this->matrix[10] = scale.z;
}

void Transform::setRotation(Vector axis, float angle)
{
	this->quaternion.setRotation(axis, angle);
	this->quaternion.getMatrix(this->matrix);
}

Vector Transform::getPosition()
{
	return Vector(this->matrix[12], this->matrix[13], this->matrix[14]);
}

Quaternion Transform::getRotation()
{
	return this->quaternion;
}

Vector Transform::getScale()
{
	return Vector(this->matrix[0], this->matrix[5], this->matrix[10]);
}

} // namespace
