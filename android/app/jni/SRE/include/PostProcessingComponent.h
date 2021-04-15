#ifndef _POST_PROCESSING_COMPONENT_H_
#define _POST_PROCESSING_COMPONENT_H_

#include "AEntityComponent.h"
#include "PostProcessingEffect.h"
#include <unordered_map>

namespace sre
{

class PostProcessingComponent : public AEntityComponent
{
DECLARE_COMPONENT()

private:
	std::unordered_map<PPE::Type, UPTR<PostProcessingEffect>> effects;

private:
	SRE_API PostProcessingComponent(Entity* entity);

public:
	SRE_API PostProcessingEffect* enqueueEffect(PPE::Type effectType);
	SRE_API PostProcessingEffect* getEffect(PPE::Type effectType);

friend class Entity;
friend class ShaderContentFactory;
friend class PostProcessingRenderer;
};


} // namespace sre

#endif
