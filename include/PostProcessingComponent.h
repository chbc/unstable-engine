#ifndef _POST_PROCESSING_COMPONENT_H_
#define _POST_PROCESSING_COMPONENT_H_

#include "AEntityComponent.h"

namespace sre
{

class SRE_API PostProcessingComponent : public AEntityComponent
{
public:
	PostProcessingComponent(Entity* entity);
};

} // namespace

#endif
