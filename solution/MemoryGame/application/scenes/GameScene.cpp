#include "GameScene.h"

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

	/* XXX
	Entity* entity = sceneManager->createPlaneEntity(glm::vec2(EngineValues::SCREEN_WIDTH, EngineValues::SCREEN_HEIGHT));
	entity->getTransform()->setPosition(glm::vec3{ 0.0f, 0.0f, -850.0f });
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("memoryGame/menu_background.png");

	sceneManager->addEntity(entity, "menu_background");
	*/

	Entity* entity = guiManager->createGUIImageEntity("memoryGame/card_1.png");
	GUIImageComponent* guiComponent = entity->getComponent<GUIImageComponent>();
	guiComponent->setUIPosition(glm::vec2(0.5f, 0.5f));

	guiManager->addEntity(entity, "card_1");
}

void GameScene::onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName)
{
	std::cout << "botao pressionado: " << entityName << std::endl;
}
