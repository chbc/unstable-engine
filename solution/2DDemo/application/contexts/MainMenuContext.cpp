#include "MainMenuContext.h"
#include <ScenesManager.h>
#include <MeshComponent.h>

using namespace sre;

void MainMenuContext::load(ScenesManager* scenesManager)
{
	Entity* cameraEntity = scenesManager->createOrthoCamera();

	Entity* entity = scenesManager->createPlaneEntity(glm::vec2{ 128.0f });
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	mesh->addMaterialComponent<SpriteMaterialComponent>("test_texture.png");
}
