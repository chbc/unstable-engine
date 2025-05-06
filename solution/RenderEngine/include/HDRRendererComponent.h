#ifndef _HDR_RENDERER_COMPONENT_H_
#define _HDR_RENDERER_COMPONENT_H_

#include "APostProcessingRendererComponent.h"
#include "memory_aliases.h"
#include <PostProcessingEffect.h>

namespace sre
{

class HDRRendererComponent : public APostProcessingRendererComponent
{
private:
	class ShaderManager* shaderManager;
	class AGraphicsWrapper* graphicsWrapper;
	UPTR<struct MeshData2D> meshData;

	class Shader* shader;
	
	uint32_t textureId;
	PostProcessingEffect* effect;

private:
	HDRRendererComponent(class PostProcessingComponent* component);

protected:
	void onPostRender(uint32_t targetFBO) override;

friend class PostProcessingRenderer;
};

}  // namespace

#endif
