#ifndef _GUI_BUTTON_COMPONENT_H_
#define _GUI_BUTTON_COMPONENT_H_

#include "AEntityComponent.h"
#include <glm/vec2.hpp>

namespace sre
{
/*
* pivot:
* 00	01
*	0.5
* 00	11
*/
class SRE_API GUIButtonComponent : public AEntityComponent
{
DECLARE_COMPONENT();

private:
	glm::vec2 extent{ 0.0f };
	glm::vec2 pivot{ 0.0f };
	glm::vec2 pivotizedExtent{ 0.0f };
	bool pressed{ false };

public:
	GUIButtonComponent(Entity* entity);
	void onInit() override;

	void setExtent(glm::vec2 extent);
	void setPivot(glm::vec2 pivot);
	bool isPressed();

private:
	bool isInside(const glm::vec2& pointPosition);
	void setPressed(bool value);

	friend class Entity;

#ifdef __ANDROID__
	friend class SDLAndroidAPI;
#else
	friend class SDLAPI;
#endif

};

} // namespace

#endif
