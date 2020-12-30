#include "GameScene.h"
#include "application/ScreenManager.h"
#include "MenuScene.h"

#include <SceneManager.h>
#include <GUIManager.h>
#include <MeshComponent.h>
#include <EngineValues.h>
#include <GUIImageComponent.h>
#include <GUIButtonComponent.h>

#include <iostream>

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

	this->setupCards(guiManager);
}

void GameScene::onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName)
{
	ScreenManager::getInstance()->changeScene(new MenuScene);
}

void GameScene::setupCards(GUIManager* guiManager)
{
	glm::vec2 position(0.125f, 0.4f);
	Entity* baseEntity = nullptr;
	Entity* charEntity = nullptr;
	Entity* descriptionEntity = nullptr;
	GUIImageComponent* guiComponent = nullptr;
	const glm::vec3 CARD_SCALE(0.45f, 0.45f, 1.0f);
	const glm::vec3 CHAR_SCALE(0.30f, 0.30f, 1.0f);

	std::string cardPaths[4] =
	{
		"memoryGame/card_1.png", "memoryGame/card_2.png", "memoryGame/card_3.png", "memoryGame/card_4.png"
	};

	std::string descriptionPaths[4] =
	{
		"memoryGame/card_1_description.png", "memoryGame/card_2_description.png", "memoryGame/card_3_description.png", "memoryGame/card_4_description.png"
	};

	for (int i = 0; i < 4; i++)
	{
		baseEntity = guiManager->createGUIImageEntity("memoryGame/base_card.png");
		guiComponent = baseEntity->getComponent<GUIImageComponent>();
		guiComponent->setUIPosition(position);

		charEntity = guiManager->createGUIImageEntity(cardPaths[i]);
		guiComponent = charEntity->getComponent<GUIImageComponent>();
		guiComponent->setUIPosition(position + glm::vec2(0.0f, -0.025f));

		descriptionEntity = guiManager->createGUIImageEntity(descriptionPaths[i]);
		guiComponent = descriptionEntity->getComponent<GUIImageComponent>();
		guiComponent->setUIPosition(position + glm::vec2(0.0f, 0.05f));
		
		/*
		baseEntity->addChild(charEntity);
		baseEntity->addChild(descriptionEntity);
		baseEntity->getTransform()->setScale(CARD_SCALE);
		*/
		baseEntity->getTransform()->setScale(CARD_SCALE);
		charEntity->getTransform()->setScale(CHAR_SCALE);
		descriptionEntity->getTransform()->setScale(CARD_SCALE);

		guiManager->addEntity(charEntity);
		guiManager->addEntity(descriptionEntity);
		guiManager->addEntity(baseEntity);

		position.x += 0.25f;
	}

	position.x = 0.125f;
	position.y = 0.6f;

	for (int i = 0; i < 4; i++)
	{
		baseEntity = guiManager->createGUIImageEntity("memoryGame/back_card.png");
		guiComponent = baseEntity->getComponent<GUIImageComponent>();
		guiComponent->setUIPosition(position);
		baseEntity->getTransform()->setScale(CARD_SCALE);

		GUIButtonComponent* button = baseEntity->addComponent<GUIButtonComponent>();
		button->setExtent(guiComponent->getExtent());

		guiManager->addEntity(baseEntity);

		position.x += 0.25f;
	}
}
