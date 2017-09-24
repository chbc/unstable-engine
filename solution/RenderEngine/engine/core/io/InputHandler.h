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
		virtual void onKeyPressed(KeyboardButton key) {}
		virtual void onKeyReleased(KeyboardButton key) {}
		virtual void onMouseMove(const glm::vec2 &position) {}
		virtual void onMouseMoveRelative(const glm::vec2 &relativePosition) {}
		virtual void onMouseButtonPressed(MouseButton mouseButton, const glm::vec2 &position) {}
		virtual void onMouseButtonReleased(MouseButton mouseButton, const glm::vec2 &position) {}
		virtual void onMouseWheel(int direction) {}

	friend class SDLAPI;
};

} // namespace

#endif
