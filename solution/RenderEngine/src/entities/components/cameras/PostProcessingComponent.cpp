#include "PostProcessingComponent.h"
#include "Entity.h"

namespace sre
{

PostProcessingComponent::PostProcessingComponent(Entity* entity) 
	: AEntityComponent(entity)
{ }

PostProcessingEffect* PostProcessingComponent::enqueueEffect(PPE::Type effectType)
{
	PostProcessingEffect* result = PostProcessingEffect::create(effectType);
	this->effects.emplace(effectType, result);

	return result;
}

PostProcessingEffect* PostProcessingComponent::getEffect(PPE::Type effectType)
{
	return this->effects[effectType].get(); // ###
}

} // namespace
