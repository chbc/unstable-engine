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

GuizmoComponent::~GuizmoComponent()
{
	if (this->subjectCollider)
	{
		this->subjectCollider->removePropertyChangedCallback(this->colliderCallbackId);
	}
}

void GuizmoComponent::loadMesh(EGuizmoType guizmoType, AColliderComponent* arg_subjectCollider)
{
	this->guizmoType = guizmoType;
	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	this->mesh = assetsManager->loadGuizmo(this->guizmoType);
	this->subjectCollider = arg_subjectCollider;

	if (this->guizmoType == EGuizmoType::MESH)
	{
		this->getEntity()->getBounds(this->bounds);
		float maxHalfExtent = std::max(this->bounds.halfExtents.x, std::max(this->bounds.halfExtents.y, this->bounds.halfExtents.z));
		if (maxHalfExtent < 0.001f)
		{
			this->bounds.reset(0.1f);
		}
	}
	else if (subjectCollider)
	{
		this->bounds = this->subjectCollider->getBounds();
		this->colliderCallbackId = subjectCollider->addPropertyChangedCallback([this](){ this->onColliderChanged(); });
	}
}

void GuizmoComponent::onColliderChanged()
{
	this->bounds = this->subjectCollider->getBounds();
}

} // namespace
