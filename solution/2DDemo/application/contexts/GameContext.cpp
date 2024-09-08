#include "GameContext.h"
#include <ScenesManager.h>
#include <MeshComponent.h>

using namespace sre;

void GameContext::load(ScenesManager* scenesManager)
{
	Entity* cameraEntity = scenesManager->createOrthoCamera();

	Entity* entity = scenesManager->createPlaneEntity(glm::vec2{ 128.0f });
	entity->getTransform()->setPosition(glm::vec3{ 400.0f, 0.0f, 0.0f });
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	SpriteMaterialComponent* sprite = mesh->addMaterialComponent<SpriteMaterialComponent>("coin_animation.png");
	mesh->setIsOpaque(false);
}
