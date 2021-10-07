#include "Input.h"

namespace sre
{

std::unordered_map<Key, bool> Input::Keys;
std::unordered_map<MouseButton, bool> Input::MouseButtons;
glm::ivec2 Input::MousePosition;
glm::ivec2 Input::MouseDeltaPosition;
int Input::MouseWheelDirection;
bool Input::CloseButton;

bool Input::isKeyDown(Key key)
{
	return (Keys.count(key) > 0);
}

bool Input::isMouseButtonDown(MouseButton button)
{
	return (MouseButtons[button]);
}

bool Input::isCloseButtonDown()
{
	return CloseButton;
}

const glm::ivec2& Input::getMousePosition()
{
	return MousePosition;
}

const glm::ivec2& Input::getMouseDeltaPosition()
{
	return MouseDeltaPosition;
}

int Input::GetMouseWheel()
{
	return MouseWheelDirection;
}

void Input::addKey(Key key)
{
	Keys[key] = true;
}

void Input::addMouseButton(MouseButton button)
{
	MouseButtons[button] = true;
}

void Input::setMousePosition(int x, int y)
{
	MousePosition.x = x;
	MousePosition.y = y;
}

void Input::setMouseDeltaPosition(int x, int y)
{
	MouseDeltaPosition.x = x;
	MouseDeltaPosition.y = y;
}

void Input::setMouseWheel(int direction)
{
	MouseWheelDirection = direction;
}

void Input::clear()
{
	Keys.clear();
	MouseButtons.clear();
	MouseDeltaPosition.x = 0;
	MouseDeltaPosition.y = 0;
	MouseWheelDirection = 0;
	CloseButton = false;
}

} // namespace
