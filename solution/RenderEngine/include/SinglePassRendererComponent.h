#pragma once

#include "APostProcessingRendererComponent.h"
#include "memory_aliases.h"

namespace sre
{

class SinglePassRendererComponent : public APostProcessingRendererComponent
{
private:
	class ShaderManager* shaderManager;
	class AGraphicsWrapper* graphicsWrapper;

	uint32_t program;
	UPTR<struct MeshData2D> meshData;
	uint32_t textureId;

private:
	SinglePassRendererComponent(class PostProcessingComponent* component);

protected:
	void onPostRender(uint32_t targetFBO) override;

friend class PostProcessingRenderer;
};

}  // namespace
