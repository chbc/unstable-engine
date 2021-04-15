#include "MenuScene.h"
#include "application/SampleApplication.h"
#include "GameScene.h"
#include "CreditsScene.h"

#include <SceneManager.h>
#include <GUIManager.h>
#include <MeshComponent.h>
#include <EngineValues.h>
#include <GUIImageComponent.h>
#include <GUIButtonComponent.h>
#include <Material.h>

#include <iostream>

void MenuScene::onInit(SceneManager* sceneManager, GUIManager* guiManager)
{
	sceneManager->createOrthoCamera();

	Entity* entity;
	GUIImageComponent* guiComponent;

	entity = sceneManager->createPlaneEntity(glm::vec2(EngineValues::SCREEN_WIDTH, EngineValues::SCREEN_HEIGHT));
	entity->getTransform()->setPosition(glm::vec3{ 0.0f, 0.0f, -850.0f });
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("memoryGame/menu_background.png");
	mesh->getMaterial()->setReceivesLight(false);
	mesh->getMaterial()->setCastShadow(false);

	sceneManager->addEntity(entity, "menu_background");

	const glm::vec2 BUTTONS_EXTENT{ 0.3f, 0.1f };

	entity = guiManager->createGUIImageEntity("memoryGame/menu_start.png", BUTTONS_EXTENT);
	guiComponent = entity->getComponent<GUIImageComponent>();
	guiComponent->setUIPosition(glm::vec2(0.175f, 0.58f));
	
	GUIButtonComponent* button = entity->addComponent<GUIButtonComponent>();
	button->setExtent(guiComponent->getExtent());

	guiManager->addEntity(entity, "menu_start");

	entity = guiManager->createGUIImageEntity("memoryGame/menu_credits.png", BUTTONS_EXTENT);
	guiComponent = entity->getComponent<GUIImageComponent>();
	guiComponent->setUIPosition(glm::vec2(0.825f, 0.58f));

	button = entity->addComponent<GUIButtonComponent>();
	button->setExtent(guiComponent->getExtent());

	guiManager->addEntity(entity, "menu_credits");
}

void MenuScene::onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName)
{
	if (entityName == "menu_start")
		SampleApplication::getInstance()->changeScene(new GameScene);
	else if (entityName == "menu_credits")
		SampleApplication::getInstance()->changeScene(new CreditsScene);
}
