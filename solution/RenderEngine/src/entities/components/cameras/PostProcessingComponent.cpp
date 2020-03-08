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
	this->effects.emplace_back(result);

	return result;
}

} // namespace
