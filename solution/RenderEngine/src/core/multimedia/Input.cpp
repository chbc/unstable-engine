#include "Input.h"

namespace sre
{

std::unordered_map<Key, bool> Input::JustPressedKeys;
std::unordered_map<MouseButton, bool> Input::JustPressedMouseButtons;
std::unordered_map<Key, bool> Input::KeysDown;
std::unordered_map<MouseButton, bool> Input::MouseButtonsDown;
glm::ivec2 Input::MousePosition;
glm::ivec2 Input::MouseDeltaPosition;
int Input::MouseWheelDirection;
bool Input::CloseButton;

bool Input::isKeyJustPressed(Key key)
{
	return JustPressedKeys[key];
}

bool Input::isMouseButtonJustPressed(MouseButton button)
{
	return JustPressedMouseButtons[button];
}

bool Input::isKeyDown(Key key)
{
	return KeysDown[key];
}

bool Input::isMouseButtonDown(MouseButton button)
{
	return MouseButtonsDown[button];
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

int Input::getMouseWheel()
{
	return MouseWheelDirection;
}

void Input::addKey(Key key)
{
	JustPressedKeys[key] = true;
	KeysDown[key] = true;
}

void Input::addMouseButton(MouseButton button)
{
	JustPressedMouseButtons[button] = true;
	MouseButtonsDown[button] = true;
}

void Input::removeKeyDown(Key key)
{
	if (KeysDown[key])
		KeysDown[key] = false;
}

void Input::removeMouseButtonDown(MouseButton button)
{
	if (MouseButtonsDown[button])
		MouseButtonsDown[button] = false;
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
	JustPressedKeys.clear();
	JustPressedMouseButtons.clear();
	MouseDeltaPosition.x = 0;
	MouseDeltaPosition.y = 0;
	MouseWheelDirection = 0;
	CloseButton = false;
}

} // namespace