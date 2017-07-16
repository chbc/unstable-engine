#include "Rect.h"

namespace sre
{

Rect::Rect(const glm::vec2 &topLeft, const glm::vec2 &bottomRight)
	: topLeft(topLeft), bottomRight(bottomRight)	// ### CONFERIR
{ }

float Rect::getWidth()
{
	return (this->bottomRight.x - this->topLeft.x);
}

float Rect::getHeight()
{
	return (this->bottomRight.y - this->topLeft.y);
}

} // namespace
