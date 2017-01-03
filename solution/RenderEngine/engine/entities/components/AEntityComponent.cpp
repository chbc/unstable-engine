#include "AEntityComponent.h"

#include <engine/entities/Entity.h>
#include <engine/entities/components/transforms/TransformComponent.h>


namespace sre
{

TransformComponent *AEntityComponent::getTransform()
{
	return this->entity->getTransform();
}

}
