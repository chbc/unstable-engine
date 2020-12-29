#include "MenuScene.h"

#include <SceneManager.h>
#include <MeshComponent.h>
#include <EngineValues.h>

void MenuScene::onInit(SceneManager* sceneManager)
{
	Entity* entity = sceneManager->createPlaneEntity(glm::vec2(EngineValues::SCREEN_WIDTH, EngineValues::SCREEN_HEIGHT));
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("memoryGame/menu_background.png");

	sceneManager->addEntity(entity, "menu_background");

	const glm::vec2 BUTTONS_SIZE{ 210.0f, 115.0f };
	entity = sceneManager->createPlaneEntity(BUTTONS_SIZE);
	entity->getTransform()->setPosition(glm::vec3{ 0.0f, -(EngineValues::SCREEN_HEIGHT * 0.2f), 1.0f });

	mesh = entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("memoryGame/menu_start.png");

	sceneManager->addEntity(entity, "menu_start");

	entity = sceneManager->createPlaneEntity(BUTTONS_SIZE);
	entity->getTransform()->setPosition(glm::vec3{ 0.0f, -(EngineValues::SCREEN_HEIGHT * 0.4f), 1.0f });
	mesh = entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("memoryGame/menu_credits.png");

	sceneManager->addEntity(entity, "menu_credits");
}

void MenuScene::onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName)
{
	// guiButton->getEntity()->getName()
}
