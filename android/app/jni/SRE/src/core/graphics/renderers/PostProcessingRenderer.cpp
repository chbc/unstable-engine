#include "PostProcessingRenderer.h"

#include "BloomRendererComponent.h"
#include "SinglePassRendererComponent.h"
#include "HDRRendererComponent.h"
#include "DOFRendererComponent.h"
#include "OutlineRendererPPComponent.h"

#include "PostProcessingComponent.h"

namespace sre
{

PostProcessingRenderer::PostProcessingRenderer()
	: useBrightnessSegmentation(false), includeDepth(false)
{ }

void PostProcessingRenderer::onSceneLoaded(PostProcessingComponent* postProcessingComponent)
{
	APostProcessingRendererComponent* rendererComponent = nullptr;

	this->useBrightnessSegmentation = false;

	for (const auto& item : postProcessingComponent->effects)
	{
		switch (item.first)
		{
			case PPE::GRAYSCALE:
			case PPE::INVERSE:
			case PPE::BLUR:
				rendererComponent = new SinglePassRendererComponent{ postProcessingComponent };
				break;
			
			case PPE::HDR:
				rendererComponent = new HDRRendererComponent{ postProcessingComponent };
				break;
			
			case PPE::BLOOM:
				rendererComponent = new BloomRendererComponent{ postProcessingComponent };
				this->useBrightnessSegmentation = true;
				break;
			case PPE::DOF:
				rendererComponent = new DOFRendererComponent{ postProcessingComponent };
				this->includeDepth = true;
				break;

			case PPE::OUTLINE:
				rendererComponent = new OutlineRendererPPComponent{ postProcessingComponent };
				break;
		}
	}

	this->component = UPTR<APostProcessingRendererComponent>{ rendererComponent };
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
