#include "PostProcessingRenderer.h"

#include "BloomRendererComponent.h"
#include "SinglePassRendererComponent.h"
#include "HDRRendererComponent.h"
#include "DOFRendererComponent.h"

#include "PostProcessingComponent.h"

namespace sre
{

PostProcessingRenderer::PostProcessingRenderer() { }

void PostProcessingRenderer::onSceneLoaded(PostProcessingComponent* postProcessingComponent)
{
	DOFRendererComponent* rendererComponent = new DOFRendererComponent{ postProcessingComponent };
	this->component = UPTR<APostProcessingRendererComponent>{ rendererComponent };

	this->useBrightnessSegmentation = false;

	for (const UPTR<PostProcessingEffect>& item : postProcessingComponent->effects)
	{
		switch (item->getType())
		{
			case PPE::BLOOM:
				this->useBrightnessSegmentation = true;
				break;
			case PPE::DOF:
				this->includeDepth = true;
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
