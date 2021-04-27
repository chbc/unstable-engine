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
	glm::vec2 extent;
	glm::vec2 pivot;

	glm::vec2 pivotizedExtent;

private:
	GUIButtonComponent(Entity* entity);

public:
	void onStart() override;

	void setExtent(glm::vec2 extent);
	void setPivot(glm::vec2 pivot);

private:
	bool isInside(const glm::vec2& pointPosition);

	friend class SDLAPI;
	friend class Entity;

#ifdef __ANDROID__
	friend class SDLAndroidAPI;
#endif
};

} // namespace

#endif
