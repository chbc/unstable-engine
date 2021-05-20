#ifndef _A_POST_PROCESSING_RENDERER_COMPONENT_H_
#define _A_POST_PROCESSING_RENDERER_COMPONENT_H_

#include <stdint.h>

namespace sre
{

class APostProcessingRendererComponent
{
protected:
	uint32_t firstPassFBO;

public:	
	virtual ~APostProcessingRendererComponent() { }

protected:
	virtual void onPostRender(uint32_t targetFBO) = 0;

friend class PostProcessingRenderer;
};

}  // namespace

#endif
