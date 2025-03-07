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
	this->showingCadsTime = 0;

	this->setupEndGameButtons(guiManager);
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

	if (this->endGameRestart->getName() == entityName)
	{
		SampleApplication::getInstance()->changeScene(new GameScene);
		return;
	}

	if (this->endGameBack->getName() == entityName)
	{
		SampleApplication::getInstance()->changeScene(new MenuScene);
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

void GameScene::setupEndGameButtons(GUIManager* guiManager)
{
	// Restart
	this->endGameRestart = guiManager->createGUIImageEntity("memoryGame/end_game_restart.png", glm::vec2(0.4f, 0.2f));
	GUIImageComponent* guiComponent = this->endGameRestart->getComponent<GUIImageComponent>();
	guiComponent->setUIPosition(glm::vec2(0.5f, 0.875f));
	
	GUIButtonComponent* button = this->endGameRestart->addComponent<GUIButtonComponent>();
	button->setExtent(guiComponent->getExtent());

	guiManager->addEntity(this->endGameRestart, "end_game_restart");
	this->endGameRestart->setEnabled(false);

	// Back
	this->endGameBack = guiManager->createGUIImageEntity("memoryGame/end_game_back.png", glm::vec2(0.15f, 0.15f));
	guiComponent = this->endGameBack->getComponent<GUIImageComponent>();
	guiComponent->setUIPosition(glm::vec2(0.1f, 0.075f));

	button = this->endGameBack->addComponent<GUIButtonComponent>();
	button->setExtent(guiComponent->getExtent());

	guiManager->addEntity(this->endGameBack, "end_game_restart");
	this->endGameBack->setEnabled(false);
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
	{
		this->endGameRestart->setEnabled(true);
		this->endGameBack->setEnabled(true);
	}
}
