#include "PostProcessingComponent.h"
#include "Entity.h"

namespace sre
{

PostProcessingComponent::PostProcessingComponent(Entity* entity) 
	: AEntityComponent(entity)
{ }

void PostProcessingComponent::addEffect(PPE::Type effectType)
{
	PostProcessingEffect* newEffect = PostProcessingEffect::create(effectType);
	this->effects.emplace_back(newEffect);
}

} // namespace
