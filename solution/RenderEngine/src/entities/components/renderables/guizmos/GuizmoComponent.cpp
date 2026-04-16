#include "GuizmoComponent.h"
#include "AssetsManager.h"
#include "SingletonsManager.h"
#include "Entity.h"
#include "AColliderComponent.h"

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

	if (this->guizmoType == EGuizmoType::MESH)
	{
		this->getEntity()->getBounds(this->bounds);
	}
	else
	{
		AColliderComponent* collider = this->getEntity()->getBaseComponent<AColliderComponent>();
		if (collider)
		{
			this->bounds = collider->getBounds();
			collider->addPropertyChangedCallback([this](){ this->onColliderChanged(); });
		}
	}
}

void GuizmoComponent::onColliderChanged()
{
	ARenderableComponent::onPropertyChanged();
	if (this->guizmoType == EGuizmoType::MESH)
	{
		this->getEntity()->getBounds(this->bounds);
	}
	else
	{
		AColliderComponent* collider = this->getEntity()->getBaseComponent<AColliderComponent>();
		if (collider)
		{
			this->bounds = collider->getBounds();
		}
	}
}

} // namespace
