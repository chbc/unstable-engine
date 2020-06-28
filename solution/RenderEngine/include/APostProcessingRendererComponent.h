#ifndef _A_POST_PROCESSING_RENDERER_COMPONENT_H_
#define _A_POST_PROCESSING_RENDERER_COMPONENT_H_

namespace sre
{

class APostProcessingRendererComponent
{
public:	
	virtual ~APostProcessingRendererComponent() { }

protected:
	virtual void onPreRender() = 0;
	virtual void onPostRender() = 0;

friend class PostProcessingRenderer;
};

}  // namespace

#endif
