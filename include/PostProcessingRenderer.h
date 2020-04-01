#ifndef _POST_PROCESSING_RENDERER_H_
#define _POST_PROCESSING_RENDERER_H_

#include "memory_aliases.h"
#include "APostProcessingRendererComponent.h"

namespace sre
{

class PostProcessingRenderer
{
private:
	UPTR<APostProcessingRendererComponent> component;
	bool useBrightnessSegmentation;
	bool includeDepth;

private:
	PostProcessingRenderer();

	void onSceneLoaded(class PostProcessingComponent* postProcessingItem);
	void onPreRender();
	void onPostRender();

	bool isUsingBrightnessSegmentation() { return this->useBrightnessSegmentation; }
	bool isIncludingDepth() { return this->includeDepth; }

friend class RenderManager;
};

} // namespace

#endif
