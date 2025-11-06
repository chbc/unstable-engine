#include "Input.h"
#include "EngineValues.h"

namespace sre
{

std::unordered_map<int, UPTR<ControllerInput>> Input::controllers;
std::set<Key> Input::JustPressedKeys;
std::set<MouseButton> Input::JustPressedMouseButtons;
std::set<Key> Input::KeysDown;
std::set<MouseButton> Input::MouseButtonsDown;
glm::ivec2 Input::MousePosition{ 0 };
glm::ivec2 Input::MouseDeltaPosition{ 0 };
int Input::MouseWheelDirection{ 0 };
bool Input::CloseButton{ false };

bool Input::isKeyJustPressed(Key key)
{
	return (JustPressedKeys.count(key) > 0);
}

bool Input::isMouseButtonJustPressed(MouseButton button)
{
	return (JustPressedMouseButtons.count(button) > 0);
}

bool Input::isKeyDown(Key key)
{
	return (KeysDown.count(key) > 0);
}

bool Input::isMouseButtonDown(MouseButton button)
{
	return (MouseButtonsDown.count(button) > 0);
}

bool Input::isCloseButtonDown()
{
	return CloseButton;
}

bool Input::isMouseMoving()
{
	return ((MouseDeltaPosition.x != 0) || (MouseDeltaPosition.y != 0));
}

const glm::ivec2& Input::getMousePixelCoordPosition()
{
	return MousePosition;
}

glm::vec3 Input::getMouseNormalizedPosition()
{
	float halfWidth = static_cast<float>(EngineValues::SCREEN_WIDTH) * 0.5f;
	float halfHeight = static_cast<float>(EngineValues::SCREEN_HEIGHT) * 0.5f;

	glm::vec3 result{ 0.0f };
	result.x = (static_cast<float>(MousePosition.x) / halfWidth) - 1.0f;
	result.y = -(static_cast<float>(MousePosition.y) / halfHeight) + 1.0f;

	return result;
}

const glm::ivec2& Input::getMouseDeltaPosition()
{
	return MouseDeltaPosition;
}

int Input::getMouseWheel()
{
	return MouseWheelDirection;
}

void Input::addController(int id)
{
	controllers[id] = UPTR<ControllerInput>{ new ControllerInput };
}

void Input::removeController(int id)
{
	controllers.erase(id);
}

ControllerInput* Input::getController(int id)
{
	return controllers[id].get();
}

void Input::addKey(Key key)
{
	JustPressedKeys.insert(key);
	KeysDown.insert(key);
}

void Input::addMouseButton(MouseButton button)
{
	JustPressedMouseButtons.insert(button);
	MouseButtonsDown.insert(button);
}

void Input::removeKeyDown(Key key)
{
	KeysDown.erase(key);
}

void Input::removeMouseButtonDown(MouseButton button)
{
	MouseButtonsDown.erase(button);
}

void Input::setMousePosition(int x, int y)
{
	MousePosition.x = x;
	MousePosition.y = y;
}

void Input::addMouseDeltaPosition(int x, int y)
{
	MouseDeltaPosition.x += x;
	MouseDeltaPosition.y += y;
}

void Input::setMouseWheel(int direction)
{
	MouseWheelDirection = direction;
}

void Input::clearTemporaryInput()
{
	JustPressedKeys.clear();
	JustPressedMouseButtons.clear();
	MouseDeltaPosition.x = 0;
	MouseDeltaPosition.y = 0;
	MouseWheelDirection = 0;
	CloseButton = false;

	for (auto& item : controllers)
	{
		item.second->clearTemporaryInput();
	}
}

} // namespace
