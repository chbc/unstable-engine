#ifndef _RECT_H_
#define _RECT_H_

#include <glm/vec2.hpp>

namespace sre
{

class Rect
{
public:
	glm::vec2 topLeft;
	glm::vec2 bottomRight;

	Rect(const glm::vec2 &topLeft, const glm::vec2 &bottomRight);

	float getWidth();
	float getHeight();
};

} // namespace

#endif
