#include "LightNode.h"

namespace nodes
{

LightNode::LightNode() : Node()
{
    this->color = Vector(0.6f, 0.6f, 0.6f);
    this->posDir = Vector(0, 1, 0);
}

void LightNode::setColor(const Vector &color)
{
    this->color = color;
}

} // namespace nodes
