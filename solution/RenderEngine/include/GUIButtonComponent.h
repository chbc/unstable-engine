#ifndef _GUI_BUTTON_H_
#define _GUI_BUTTON_H_

#include "AEntityComponent.h"
#include <glm/vec2.hpp>

namespace sre
{

class Entity;

class GUIButtonComponent : public AEntityComponent
{
private:
	glm::vec2 halfExtent;

private:
	GUIButtonComponent(Entity* entity, glm::vec2 arg_extent);

	bool isInside(const glm::vec2& pointPosition);

public:
	void onStart() override;

	friend class SDLAPI;

};


} // namespace

#endif
