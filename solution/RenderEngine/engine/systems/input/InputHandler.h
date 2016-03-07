#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <engine/math/Vector.h>
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
		virtual void onMouseMove(Vector relativePosition) {}
		virtual void onMouseButtonPressed(MouseButton mouseButton, Vector position) {}
		virtual void onMouseButtonReleased(MouseButton mouseButton, Vector position) {}

	friend class SDLAPI;
};

} // namespace

#endif
