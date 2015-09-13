#include "CameraNode.h"

namespace nodes
{

CameraNode::CameraNode() : Node()
{
	this->up.y = 1;
    this->setPosition(Vector(0.0f, 0.0f, 2.0f));
    this->lookTarget = Vector::ZERO;
}

void CameraNode::setLookAt(const Vector &target)
{
	this->lookTarget = target;
}

} // namespace nodes
