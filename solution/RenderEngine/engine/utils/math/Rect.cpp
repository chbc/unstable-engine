#include "Rect.h"

namespace sre
{

Rect::Rect() : topLeft(glm::vec2(0, 0)), size(glm::vec2(0, 0)) { }

Rect::Rect(const glm::vec2 &topLeft, const glm::vec2 &size)
	: topLeft(topLeft), size(size)
{ }

} // namespace
