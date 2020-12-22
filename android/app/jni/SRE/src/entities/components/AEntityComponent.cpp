#include "AEntityComponent.h"

#include "Entity.h"
#include "TransformComponent.h"

namespace sre
{

TransformComponent *AEntityComponent::getTransform()
{
	return this->entity->getTransform();
}

}
