#pragma once

#include "APostProcessingRendererComponent.h"
#include "memory_aliases.h"

namespace sre
{

class DOFRendererComponent : public APostProcessingRendererComponent
{
private:
	class ShaderManager* shaderManager;
	class AGraphicsWrapper* graphicsWrapper;
	UPTR<struct MeshData2D> meshData;

	uint32_t program;
	
	uint32_t initialPassTextureId;
	uint32_t brightnessTextureId;
	uint32_t depthTextureId;

	uint32_t fbo;

private:
	DOFRendererComponent(class PostProcessingComponent* component);

protected:
	void onPostRender(uint32_t targetFBO) override;

friend class PostProcessingRenderer;
};

}  // namespace
