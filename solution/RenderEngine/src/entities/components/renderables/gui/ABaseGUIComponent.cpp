#include "ABaseGUIComponent.h"

#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "Texture.h"

namespace sre
{

ABaseGUIComponent::ABaseGUIComponent(Entity* entity) : ARenderableComponent(entity)
{ }

void ABaseGUIComponent::onPropertyDeserialized()
{
	AEntityComponent::onPropertyDeserialized();
	this->loadMesh();
}

void ABaseGUIComponent::loadMesh()
{
	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	this->meshData = assetsManager->loadMesh2D();
}

} // namespace
