#include "GameContext.h"
#include <ScenesManager.h>
#include <MeshComponent.h>

using namespace sre;

void GameContext::load(ScenesManager* scenesManager)
{
	Entity* cameraEntity = scenesManager->createPerspectiveCamera();
	cameraEntity->getTransform()->setPosition(glm::vec3{ 0.0f, 5.0f, 5.0f });

	Entity* meshEntity = scenesManager->createCubeEntity();
	meshEntity->getTransform()->setRotation(glm::vec3{ 0.0f, 1.0f, 0.0f }, 90.0f);
	meshEntity->getComponent<MeshComponent>()->getMaterial()->setReceivesLight(true);
	DirectionalLightComponent* light = scenesManager->createDirectionalLight();
	light->setDirection(glm::vec3{ 1.0f, -1.0f, 0.0f });
	// entity->getTransform()->setPosition(glm::vec3{ 2.0f, 3.0f, 4.0f });

	/*
	Entity* entity = scenesManager->createPlaneEntity(glm::vec2{ 128.0f }, 1.0, "coin");
	MeshComponent* mesh = entity->getComponent<MeshComponent>();
	DiffuseMaterialComponent* sprite = mesh->addMaterialComponent<DiffuseMaterialComponent>("coin_animation.png");
	mesh->setIsOpaque(false);
	
	Material* material = mesh->getMaterial();
	material->setUVTiling(glm::vec2(0.1666f, 1.0f));
	*/
}
