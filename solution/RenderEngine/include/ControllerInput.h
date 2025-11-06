#pragma once

#include "core_defines.h"

#include <set>
#include <glm/vec2.hpp>

enum class ControllerButton
{
    BUTTON_INVALID = -1,
    BUTTON_A,
    BUTTON_B,
    BUTTON_X,
    BUTTON_Y,
    BUTTON_BACK,
    BUTTON_GUIDE,
    BUTTON_START,
    BUTTON_LEFTSTICK,
    BUTTON_RIGHTSTICK,
    BUTTON_LEFTSHOULDER,
    BUTTON_RIGHTSHOULDER,
    BUTTON_DPAD_UP,
    BUTTON_DPAD_DOWN,
    BUTTON_DPAD_LEFT,
    BUTTON_DPAD_RIGHT,
    BUTTON_MISC1,
    BUTTON_PADDLE1,
    BUTTON_PADDLE2,
    BUTTON_PADDLE3,
    BUTTON_PADDLE4,
    BUTTON_TOUCHPAD,
    BUTTON_MAX
};

namespace sre
{

class SRE_API ControllerInput
{
private:
	std::set<ControllerButton> justPressedButtons;
	std::set<ControllerButton> buttonsDown;
	glm::vec2 analogLeft;
	glm::vec2 analogRight;
    glm::vec2 triggers;

public:
    bool isButtonJustPressed(ControllerButton button) const;
    bool isButtonDown(ControllerButton button) const;
    const glm::vec2& getAnalogLeft() const;
    const glm::vec2& getAnalogRight() const;

private:
    void addButtonPress(ControllerButton button);
    void removeButtonDown(ControllerButton button);
	void clearTemporaryInput();

friend class Input;
friend class SDLAPI;
};

} // namespace
