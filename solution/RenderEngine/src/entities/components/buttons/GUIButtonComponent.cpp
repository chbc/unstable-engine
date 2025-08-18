#include "GUIButtonComponent.h"
#include "SingletonsManager.h"
#include "MultimediaManager.h"
#include "TransformComponent.h"

namespace sre
{

IMPLEMENT_COMPONENT(GUIButtonComponent)

GUIButtonComponent::GUIButtonComponent(Entity* entity) 
	: AEntityComponent(entity), pivot(glm::vec2{0.5f, 0.5f})
{
}

void GUIButtonComponent::onInit()
{
	MultimediaManager* multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();
	multimediaManager->addGUIButton(this);
}

void GUIButtonComponent::setExtent(glm::vec2 extent)
{
	this->extent = extent;
	this->pivotizedExtent = this->extent * this->pivot;
}

void GUIButtonComponent::setPivot(glm::vec2 pivot)
{
	this->pivot = pivot;
	this->pivotizedExtent = this->extent * this->pivot;
}

bool GUIButtonComponent::isPressed()
{
	return this->pressed;
}

bool GUIButtonComponent::isInside(const glm::vec2& pointPosition)
{
	// 0 <-> -1
	// 1 <-> 1
	// 0.5 <-> 0

	// 0 -> 0.5
	// 1 -> 0
	// -1 -> 1

	glm::vec3 position = this->getTransform()->getPosition();
	glm::vec2 uiPosition((position.x + 1.0f) * 0.5f, -(position.y - 1.0f) * 0.5f);

	bool result =
	(
		(
			(pointPosition.x > (uiPosition.x - this->pivotizedExtent.x))
			&&
			(pointPosition.x < (uiPosition.x + this->extent.x - this->pivotizedExtent.x))
		)
		&&
		(
			(pointPosition.y > (uiPosition.y - this->pivotizedExtent.y))
			&&
			(pointPosition.y < (uiPosition.y + this->extent.y - this->pivotizedExtent.y))
		)
	);

	return result;
}

void GUIButtonComponent::setPressed(bool value)
{
	this->pressed = value;
}

} // namespace
