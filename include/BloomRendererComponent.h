#ifndef _BLOOM_RENDERER_COMPONENT_H_
#define _BLOOM_RENDERER_COMPONENT_H_

#include "APostProcessingRendererComponent.h"
#include "memory_aliases.h"

namespace sre
{

class BloomRendererComponent : public APostProcessingRendererComponent
{
private:
	class ShaderManager* shaderManager;
	class AGraphicsWrapper* graphicsWrapper;

	class Shader* initialPassShader;
	class Shader* finalPassShader;
	UPTR<struct GUIMeshData> meshData;
	uint32_t initialPassTextureId;
	uint32_t finalPassTextureId;

	uint32_t initialPassFBO;
	uint32_t finalPassFBO;

private:
	BloomRendererComponent(class PostProcessingComponent* component);

protected:
	void onPreRender();
	void onPostRender();

friend class PostProcessingRenderer;
};

}  // namespace

#endif
