#pragma once

#include "core_defines.h"
#include "button_names.h"

#include <unordered_map>
#include <bitset>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace sre
{

class SRE_API Input
{
private:
	static std::unordered_map<Key, bool> JustPressedKeys;
	static std::unordered_map<MouseButton, bool> JustPressedMouseButtons;
	static std::unordered_map<Key, bool> KeysDown;
	static std::unordered_map<MouseButton, bool> MouseButtonsDown;
	static glm::ivec2 MousePosition;
	static glm::ivec2 MouseDeltaPosition;
	static int MouseWheelDirection;
	static bool CloseButton;

public:
	static bool isKeyJustPressed(Key key);
	static bool isMouseButtonJustPressed(MouseButton button);
	static bool isKeyDown(Key key);
	static bool isMouseButtonDown(MouseButton button);
	static bool isCloseButtonDown();
	static bool isMouseMoving();
	static const glm::ivec2& getMousePixelCoordPosition();
	static glm::vec3 getMouseNormalizedPosition();
	static const glm::ivec2& getMouseDeltaPosition();
	static int getMouseWheel();

private:
	static void addKey(Key key);
	static void addMouseButton(MouseButton button);
	static void removeKeyDown(Key key);
	static void removeMouseButtonDown(MouseButton button);
	static void setMousePosition(int x, int y);
	static void setMouseDeltaPosition(int x, int y);
	static void setMouseWheel(int direction);
	static void clear();

friend class SDLAPI;
};

} // namespace
