#include "Card.h"

#include <GUIManager.h>
#include <cstdio>

#ifdef __ANDROID__
	#define SPRINTF std::sprintf
#else
	#define SPRINTF sprintf_s
#endif

Card::Card(GUIManager* guiManager, const glm::vec2& position, int arg_id, int entityId) : cardId(arg_id), isRevealed(false)
{
	Entity* baseEntity = guiManager->createGUIImageEntity("memoryGame/base_card.png", this->CARD_EXTENT);
	GUIImageComponent* guiComponent = baseEntity->getComponent<GUIImageComponent>();
	guiComponent->setUIPosition(position);

	char path[128];

	SPRINTF(path, CARD_CHAR_PATH, this->cardId + 1);

	Entity* charEntity = guiManager->createGUIImageEntity(path, this->CHAR_EXTENT);
	charEntity->getTransform()->setLocalPosition(glm::vec3(0.0f, 0.05f, 1.0f));

	SPRINTF(path, CARD_DESCRIPTION_PATH, this->cardId + 1);

	Entity* descriptionEntity = guiManager->createGUIImageEntity(path, this->DESCRIPTION_EXTENT);
	descriptionEntity->getTransform()->setLocalPosition(glm::vec3(0.0f, -0.18f, 1.0f));

	this->cover = guiManager->createGUIImageEntity("memoryGame/back_card.png", this->CARD_EXTENT);
	this->cover->getTransform()->setLocalPosition(glm::vec3(0.0f, 0.0f, 1.0f));

	baseEntity->addChild(charEntity);
	baseEntity->addChild(descriptionEntity);
	baseEntity->addChild(this->cover);

	GUIButtonComponent* button = baseEntity->addComponent<GUIButtonComponent>();
	button->setExtent(guiComponent->getExtent());

	char entityNameTemp[64];

	SPRINTF(entityNameTemp, "card_%d", entityId);

	this->entityName = entityNameTemp;

	guiManager->addEntity(baseEntity, this->entityName);
}

void Card::setRevealed(bool value)
{
	this->isRevealed = value;
	this->cover->setEnabled(!this->isRevealed);
}

const std::string& Card::getEntityName()
{
	return this->entityName;
}
