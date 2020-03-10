#include "PostProcessingRenderer.h"

#include "BloomRendererComponent.h"
#include "SinglePassRendererComponent.h"


namespace sre
{

PostProcessingRenderer::PostProcessingRenderer() { }

void PostProcessingRenderer::onSceneLoaded(PostProcessingComponent* component)
{
	// ### this->components.emplace(PPE::BLOOM, new BloomRendererComponent);

	BloomRendererComponent* rendererComponent = new BloomRendererComponent{ component };
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
