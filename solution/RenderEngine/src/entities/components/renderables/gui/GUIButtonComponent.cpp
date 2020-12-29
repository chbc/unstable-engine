#include "GuiButtonComponent.h"
#include "SingletonsManager.h"
#include "MultimediaManager.h"
#include "TransformComponent.h"

namespace sre
{

GUIButtonComponent::GUIButtonComponent(Entity* entity, glm::vec2 arg_extent)
	: AEntityComponent(entity), halfExtent(arg_extent * 0.5f)
{
}

void GUIButtonComponent::onStart()
{
	MultimediaManager* multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();
	multimediaManager->addGUIButton(this);
}

bool GUIButtonComponent::isInside(const glm::vec2& pointPosition)
{
	glm::vec3 position = this->getTransform()->getPosition();

	return
	(
		((pointPosition.x > (position.x - this->halfExtent.x)) && (pointPosition.x < (position.x + this->halfExtent.x)))
		&&
		((pointPosition.y > (position.y - this->halfExtent.y)) && (pointPosition.y < (position.y + this->halfExtent.y)))
	);
}

} // namespace
