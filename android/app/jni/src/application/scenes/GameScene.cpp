#include "GameScene.h"
#include "application/SampleApplication.h"
#include "MenuScene.h"
#include "application/entities/Card.h"

#include <SceneManager.h>
#include <GUIManager.h>
#include <MeshComponent.h>
#include <EngineValues.h>
#include <GUIImageComponent.h>
#include <GUIButtonComponent.h>

#include <iostream>
#include <ctime>

void GameScene::onInit(SceneManager* sceneManager, GUIManager* guiManager)
{
	sceneManager->createOrthoCamera();

	Entity* entity = sceneManager->createPlaneEntity(glm::vec2(EngineValues::SCREEN_WIDTH, EngineValues::SCREEN_HEIGHT));
	entity->getTransform()->setPosition(glm::vec3{ 0.0f, 0.0f, -850.0f });
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("memoryGame/game_background.png");
	mesh->getMaterial()->setReceivesLight(false);
	mesh->getMaterial()->setCastShadow(false);

	sceneManager->addEntity(entity, "game_background");

	this->previousSelectedCard = nullptr;
	this->showingSelectedCards = false;
	this->showingCadsTime = 0.0f;

	this->setupEndGameMessage(guiManager);
	this->setupCards(guiManager);
}

void GameScene::onUpdate(unsigned int elapsedTime)
{
	if (this->showingSelectedCards)
	{
		this->showingCadsTime -= elapsedTime;
		if (this->showingCadsTime < 0)
		{
			this->currentSelectedCard->setRevealed(false);
			this->previousSelectedCard->setRevealed(false);
			this->currentSelectedCard = nullptr;
			this->previousSelectedCard = nullptr;
			this->showingSelectedCards = false;
		}
	}
}

void GameScene::onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName)
{
	if (this->showingSelectedCards)
		return;

	if (this->endGameMessage->getName() == entityName)
	{
		SampleApplication::getInstance()->changeScene(new GameScene);
		return;
	}

	for (const auto& item : this->cards)
	{
		if (item->getEntityName() == entityName)
		{
			if (!item->getIsRevealed())
				this->processSelectedCard(item.get());

			break;
		}
	}
}

void GameScene::setupCards(GUIManager* guiManager)
{
	glm::vec2 position(0.125f, 0.365f);
	Entity* charEntity = nullptr;
	Entity* descriptionEntity = nullptr;
	GUIImageComponent* guiComponent = nullptr;

	const glm::vec2 CARD_EXTENT(0.245f, 0.255f);
	const glm::vec3 CHAR_SCALE(0.30f, 0.30f, 1.0f);
	const int UNIQUE_CARDS = 4;

	std::vector<int> ids{ 0, 0, 1, 1, 2, 2, 3, 3 };
	srand(time(NULL));

	for (int i = 0; i < UNIQUE_CARDS; i++)
	{
		int index = rand() % ids.size();
		int id = ids[index];
		ids.erase(ids.begin() + index);

		Card* card = new Card{ guiManager, position, id, i };
		this->cards.push_back(UPTR<Card>(card));
		position.x += 0.25f;
	}

	position.x = 0.125f;
	position.y = 0.635f;
	Entity* baseEntity;
	for (int i = 0; i < UNIQUE_CARDS; i++)
	{
		int index = rand() % ids.size();
		int id = ids[index];
		ids.erase(ids.begin() + index);

		Card* card = new Card{ guiManager, position, id, UNIQUE_CARDS + i };
		this->cards.push_back(UPTR<Card>(card));
		position.x += 0.25f;
	}
}

void GameScene::setupEndGameMessage(GUIManager* guiManager)
{
	this->endGameMessage = guiManager->createGUIImageEntity("memoryGame/end_game_message.png", glm::vec2(0.75f, 0.25f));
	GUIImageComponent* guiComponent = this->endGameMessage->getComponent<GUIImageComponent>();
	guiComponent->setUIPosition(glm::vec2(0.5f, 0.125f));
	
	GUIButtonComponent* button = this->endGameMessage->addComponent<GUIButtonComponent>();
	button->setExtent(guiComponent->getExtent());

	guiManager->addEntity(this->endGameMessage, "end_game_message");
	this->endGameMessage->setEnabled(false);
}

void GameScene::processSelectedCard(Card* card)
{
	card->setRevealed(true);

	if (this->previousSelectedCard == nullptr)
	{
		this->previousSelectedCard = card;
	}
	else if (card->getId() == this->previousSelectedCard->getId())
	{
		this->previousSelectedCard = nullptr;
		this->onCardsMatch();
	}
	else
	{
		this->currentSelectedCard = card;
		this->showingCadsTime = MAX_SHOW_CARDS_TIME;
		this->showingSelectedCards = true;
	}
}

void GameScene::onCardsMatch()
{
	bool areAllCardsRevealed = true;
	for (auto& item : this->cards)
	{
		if (!item->getIsRevealed())
		{
			areAllCardsRevealed = false;
			break;
		}
	}

	if (areAllCardsRevealed)
		this->endGameMessage->setEnabled(true);
}
