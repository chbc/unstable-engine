#include "GameContext.h"
#include <ScenesManager.h>
#include <MeshComponent.h>

using namespace sre;

void GameContext::load(ScenesManager* scenesManager)
{
	Entity* cameraEntity = scenesManager->createOrthoCamera();

	Entity* entity = scenesManager->createPlaneEntity(glm::vec2{ 128.0f }, 1.0, "coin");
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	DiffuseMaterialComponent* sprite = mesh->addMaterialComponent<DiffuseMaterialComponent>("coin_animation.png");
	mesh->setIsOpaque(false);
	
	Material* material = mesh->getMaterial();
	material->setUVTiling(glm::vec2(0.1666f, 1.0f));
}
