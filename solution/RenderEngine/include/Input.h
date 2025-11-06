#pragma once

#include "button_names.h"
#include "ControllerInput.h"
#include "memory_aliases.h"

#include <unordered_map>
#include <set>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace sre
{

class SRE_API Input
{
private:
	static std::unordered_map<int, UPTR<ControllerInput>> controllers;
	static std::set<Key> JustPressedKeys;
	static std::set<MouseButton> JustPressedMouseButtons;
	static std::set<Key> KeysDown;
	static std::set<MouseButton> MouseButtonsDown;
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
	static ControllerInput* getController(int id);

private:
	static void addController(int id);
	static void removeController(int id);
	static void addKey(Key key);
	static void addMouseButton(MouseButton button);
	static void removeKeyDown(Key key);
	static void removeMouseButtonDown(MouseButton button);
	static void setMousePosition(int x, int y);
	static void addMouseDeltaPosition(int x, int y);
	static void setMouseWheel(int direction);
	static void clearTemporaryInput();

friend class SDLAPI;
};

} // namespace
