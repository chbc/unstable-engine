#include "ControllerInput.h"

namespace sre
{

bool ControllerInput::isButtonJustPressed(ControllerButton button) const
{
	return (this->justPressedButtons.count(button) > 0);
}

bool ControllerInput::isButtonDown(ControllerButton button) const
{
	return false;
}

const glm::vec2& ControllerInput::getAnalogLeft() const
{
	return this->analogLeft;
}

const glm::vec2& ControllerInput::getAnalogRight() const
{
	return this->analogRight;
}

void ControllerInput::addButtonPress(ControllerButton button)
{
	this->justPressedButtons.insert(button);
	this->buttonsDown.insert(button);
}

void ControllerInput::removeButtonDown(ControllerButton button)
{
	this->buttonsDown.erase(button);
}

void ControllerInput::clearTemporaryInput()
{
	this->justPressedButtons.clear();
}

} // namespace
