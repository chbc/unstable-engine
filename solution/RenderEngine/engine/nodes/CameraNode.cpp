#include "CameraNode.h"

namespace sre
{

CameraNode::CameraNode() : Node()
{
    this->up = Vector(0.0f, 1.0f, 0.0f);
    this->setPosition(Vector(0.0f, 0.0f, 2.0f));
    this->lookTarget = Vector::ZERO;
}

void CameraNode::setLookAt(const Vector &target)
{
	this->lookTarget = target;
}

} // namespace
