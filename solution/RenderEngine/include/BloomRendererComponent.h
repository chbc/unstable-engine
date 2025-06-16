#pragma once

#include "APostProcessingRendererComponent.h"
#include "memory_aliases.h"

namespace sre
{

class BloomRendererComponent : public APostProcessingRendererComponent
{
private:
	class ShaderManager* shaderManager;
	class AGraphicsWrapper* graphicsWrapper;
	UPTR<struct MeshData2D> meshData;

	uint32_t blurProgram;
	uint32_t combineProgram;
	
	uint32_t initialPassTextureId;
	uint32_t brightnessTextureId;
	uint32_t blurTextureIds[2];

	uint32_t blurFBOs[2];

	uint32_t blurInteractionsCount = 10;

private:
	BloomRendererComponent(class PostProcessingComponent* component);

protected:
	void onPostRender(uint32_t targetFBO) override;

friend class PostProcessingRenderer;
};

}  // namespace
