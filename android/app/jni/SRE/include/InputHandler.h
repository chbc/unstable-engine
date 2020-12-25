#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <glm/vec2.hpp>
#include "button_names.h"

namespace sre
{

class SDLAPI;

/*!
	Abstract class for process input events.
	An Event Receiver class must be created to receive input events.
*/
class InputHandler
{
	public:
		virtual ~InputHandler() {}

	protected:
		virtual void onQuit() {}
		virtual void onKeyEvent(KeyboardButton key, bool pressed) {}
		virtual void onMouseMove(const glm::vec2 &position) {}
		virtual void onMouseMoveRelative(const glm::vec2 &relativePosition) {}
		virtual void onMouseButtonEvent(MouseButton mouseButton, const glm::vec2 &position, bool pressed) {}
		virtual void onMouseWheel(int direction) {}

	friend class SDLAPI;

#ifdef __ANDROID__
	friend class SDLAndroidAPI;
#endif
};

} // namespace

#endif
