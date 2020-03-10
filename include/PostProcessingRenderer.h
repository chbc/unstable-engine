#ifndef _POST_PROCESSING_RENDERER_H_
#define _POST_PROCESSING_RENDERER_H_

#include "memory_aliases.h"
#include <unordered_map>
#include "PostProcessingEffect.h"
#include "APostProcessingRendererComponent.h"

namespace sre
{

class PostProcessingRenderer
{
private:
	// std::unordered_map<PPE::Type, UPTR<APostProcessingRendererComponent>> components;
	UPTR<APostProcessingRendererComponent> component;

private:
	PostProcessingRenderer();

	void onSceneLoaded(class PostProcessingComponent* postProcessingItem);
	void onPreRender();
	void onPostRender();

friend class RenderManager;
};

} // namespace

#endif
