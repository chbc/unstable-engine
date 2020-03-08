#ifndef _POST_PROCESSING_COMPONENT_H_
#define _POST_PROCESSING_COMPONENT_H_

#include "AEntityComponent.h"
#include "PostProcessingEffect.h"
#include <vector>

namespace sre
{

class PostProcessingComponent : public AEntityComponent
{
private:
	VECTOR_UPTR<PostProcessingEffect> effects;

private:
	SRE_API PostProcessingComponent(Entity* entity);

public:
	SRE_API PostProcessingEffect* enqueueEffect(PPE::Type effectType);

friend class Entity;
friend class ShaderContentFactory;
};


} // namespace sre

#endif
