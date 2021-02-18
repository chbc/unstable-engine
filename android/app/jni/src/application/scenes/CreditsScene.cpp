#include "CreditsScene.h"
#include "application/SampleApplication.h"
#include <MeshComponent.h>
#include "MenuScene.h"
#include <SceneManager.h>
#include <GUIManager.h>

void CreditsScene::onInit(SceneManager* sceneManager, GUIManager* guiManager)
{
	sceneManager->createOrthoCamera();

	Entity* entity;
	GUIImageComponent* guiComponent;

	entity = sceneManager->createPlaneEntity(glm::vec2(EngineValues::SCREEN_WIDTH, EngineValues::SCREEN_HEIGHT));
	entity->getTransform()->setPosition(glm::vec3{ 0.0f, 0.0f, -850.0f });
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("memoryGame/credits_background.png");
	mesh->getMaterial()->setReceivesLight(false);
	mesh->getMaterial()->setCastShadow(false);

	sceneManager->addEntity(entity, "credits_background");

	// Back button
	Entity* endGameBack = guiManager->createGUIImageEntity("memoryGame/end_game_back.png", glm::vec2(0.4f, 0.2f));
	guiComponent = endGameBack->getComponent<GUIImageComponent>();
	guiComponent->setUIPosition(glm::vec2(0.5f, 0.875f));

	GUIButtonComponent* button = endGameBack->addComponent<GUIButtonComponent>();
	button->setExtent(guiComponent->getExtent());

	guiManager->addEntity(endGameBack, "end_game_back");
}

void CreditsScene::onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName)
{
	SampleApplication::getInstance()->changeScene(new MenuScene);
}
