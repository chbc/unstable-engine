#pragma once

#include "APostProcessingRendererComponent.h"
#include "memory_aliases.h"

namespace sre
{

class OutlineRendererPPComponent : public APostProcessingRendererComponent
{
private:
	class ShaderManager* shaderManager;
	class AGraphicsWrapper* graphicsWrapper;
	UPTR<struct MeshData2D> meshData;

	uint32_t outlineProgram;
	uint32_t combineProgram;
	
	uint32_t initialPassTextureId;
	uint32_t colorSourceTextureId;
	uint32_t outlineTextureId;

	uint32_t outlinePassFBO;

private:
	OutlineRendererPPComponent(class PostProcessingComponent* component);

protected:
	void onPostRender(uint32_t targetFBO) override;

friend class PostProcessingRenderer;
};

}  // namespace
