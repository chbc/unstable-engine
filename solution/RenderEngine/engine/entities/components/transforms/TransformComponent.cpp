#include "TransformComponent.h"

namespace sre
{

/*
	Matrix Format
	0	4	8	12
	1	5	9	13
	2	6	10	14
	3	7	11	15
*/
TransformComponent::TransformComponent(Entity *entity) : AEntityComponent(entity)
{
	this->matrix = new float[16];
	this->loadIdentity();
}

TransformComponent::~TransformComponent()
{
	delete this->matrix;
}

void TransformComponent::loadIdentity()
{
	for (int i = 0; i < 16; i++)
	{
		if ((i == 0) || (i == 5) || (i == 10) || (i == 15))
			this->matrix[i] = 1;
		else
			this->matrix[i] = 0;
	}
}

void TransformComponent::setPosition(Vector position)
{
	this->matrix[12] = position.x;
	this->matrix[13] = position.y;
	this->matrix[14] = position.z;
}

void TransformComponent::setScale(Vector scale)
{
	this->matrix[0] = scale.x;
	this->matrix[5] = scale.y;
	this->matrix[10] = scale.z;
}

void TransformComponent::setRotation(Vector axis, float angle)
{
	this->quaternion.setRotation(axis, angle);
	this->quaternion.getMatrix(this->matrix);
}

Vector TransformComponent::getPosition()
{
	return Vector(this->matrix[12], this->matrix[13], this->matrix[14]);
}

Quaternion TransformComponent::getRotation()
{
	return this->quaternion;
}

Vector TransformComponent::getScale()
{
	return Vector(this->matrix[0], this->matrix[5], this->matrix[10]);
}

} // namespace
