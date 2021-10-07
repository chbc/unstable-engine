#pragma once

#include "core_defines.h"
#include "button_names.h"
#include <unordered_map>
#include <bitset>
#include <glm/vec2.hpp>

namespace sre
{

class SRE_API Input
{
private:
	static std::unordered_map<Key, bool> Keys;
	static std::unordered_map<MouseButton, bool> MouseButtons;
	static glm::ivec2 MousePosition;
	static glm::ivec2 MouseDeltaPosition;
	static int MouseWheelDirection;
	static bool CloseButton;

public:
	static bool isKeyDown(Key key);
	static bool isMouseButtonDown(MouseButton button);
	static bool isCloseButtonDown();
	static const glm::ivec2& getMousePosition();
	static const glm::ivec2& getMouseDeltaPosition();
	static int GetMouseWheel();

private:
	static void addKey(Key key);
	static void addMouseButton(MouseButton button);
	static void setMousePosition(int x, int y);
	static void setMouseDeltaPosition(int x, int y);
	static void setMouseWheel(int direction);
	static void clear();

friend class SDLAPI;
};

} // namespace
