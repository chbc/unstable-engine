#include "MenuScene.h"
#include "application/ScreenManager.h"
#include "application/scenes/GameScene.h"

#include <SceneManager.h>
#include <GUIManager.h>
#include <MeshComponent.h>
#include <EngineValues.h>
#include <GUIImageComponent.h>
#include <GUIButtonComponent.h>

#include <iostream>

void MenuScene::onInit(SceneManager* sceneManager, GUIManager* guiManager)
{
	sceneManager->createOrthoCamera();

	Entity* entity = sceneManager->createPlaneEntity(glm::vec2(EngineValues::SCREEN_WIDTH, EngineValues::SCREEN_HEIGHT));
	entity->getTransform()->setPosition(glm::vec3{ 0.0f, 0.0f, -850.0f });
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("memoryGame/menu_background.png");

	sceneManager->addEntity(entity, "menu_background");

	const glm::vec2 BUTTONS_SIZE{ 210.0f, 115.0f };
	entity = guiManager->createGUIImageEntity("memoryGame/menu_start.png");
	GUIImageComponent* guiComponent = entity->getComponent<GUIImageComponent>();
	guiComponent->setUIPosition(glm::vec2(0.5f, 0.5f));
	
	GUIButtonComponent* button = entity->addComponent<GUIButtonComponent>();
	button->setExtent(guiComponent->getExtent());

	guiManager->addEntity(entity, "menu_start");

	entity = guiManager->createGUIImageEntity("memoryGame/menu_credits.png");
	guiComponent = entity->getComponent<GUIImageComponent>();
	guiComponent->setUIPosition(glm::vec2(0.5f, 0.75f));

	guiManager->addEntity(entity, "menu_credits");
}

void MenuScene::onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName)
{
	std::cout << "botao pressionado: " << entityName << std::endl;

	ScreenManager::getInstance()->changeScene(new GameScene);
}
