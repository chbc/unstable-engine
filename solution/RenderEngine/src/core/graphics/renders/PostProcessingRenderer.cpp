#include "PostProcessingRenderer.h"

#include "BloomRendererComponent.h"
#include "SinglePassRendererComponent.h"
#include "HDRRendererComponent.h"

#include "PostProcessingComponent.h"

namespace sre
{

PostProcessingRenderer::PostProcessingRenderer() { }

void PostProcessingRenderer::onSceneLoaded(PostProcessingComponent* postProcessingComponent)
{
	HDRRendererComponent* rendererComponent = new HDRRendererComponent{ postProcessingComponent };
	this->component = UPTR<APostProcessingRendererComponent>{ rendererComponent };

	this->useBrightnessSegmentation = false;

	for (const UPTR<PostProcessingEffect>& item : postProcessingComponent->effects)
	{
		if (item->getType() == PPE::BLOOM)
		{
			this->useBrightnessSegmentation = true;
			break;
		}
	}
}

void PostProcessingRenderer::onPreRender()
{
	this->component->onPreRender();
}

void PostProcessingRenderer::onPostRender()
{
	this->component->onPostRender();
}

} // namespace
