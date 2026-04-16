#include "GuizmoComponent.h"
#include "AssetsManager.h"
#include "SingletonsManager.h"

namespace sre
{

IMPLEMENT_COMPONENT(GuizmoComponent)

GuizmoComponent::GuizmoComponent(Entity* entity) : ARenderableComponent(entity)
{ }

void GuizmoComponent::loadMesh(EGuizmoType guizmoType)
{
	this->guizmoType = guizmoType;
	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	this->mesh = assetsManager->loadGuizmo(this->guizmoType);

}

} // namespace
