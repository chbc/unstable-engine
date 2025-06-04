#ifndef _RECT_H_
#define _RECT_H_

#include <glm/vec2.hpp>

namespace sre
{

class Rect
{
public:
	glm::vec2 topLeft{ 0.0f };
	glm::vec2 size{ 0.0f };

	Rect();
	Rect(const glm::vec2 &topLeft, const glm::vec2 &size);
};

} // namespace

#endif
