#include "TestChildComponent.h"

#include <Entity.h>
#include <BoxColliderComponent.h>
#include <Log.h>

IMPLEMENT_COMPONENT(TestChildComponent)

TestChildComponent::TestChildComponent(Entity* entity) : AEntityComponent(entity) {}

void TestChildComponent::onInit()
{
	Log::LogMessage("TestChildComponent initialized");

	BoxColliderComponent* boxCollider = this->getEntity()->getComponent<BoxColliderComponent>();
	if (boxCollider)
	{
		Log::LogMessage("boxCollider OK");
	}
	else
	{
		Log::LogMessage("boxCollider FAIL");
	}

	AColliderComponent* collider = this->getEntity()->getBaseComponent<AColliderComponent>();
	if (collider)
	{
		Log::LogMessage("collider OK");
	}
	else
	{
		Log::LogMessage("collider FAIL");
	}
}
