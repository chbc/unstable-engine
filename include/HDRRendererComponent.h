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
	UPTR<struct GUIMeshData> meshData;

	class Shader* shader;
	
	uint32_t fbo;
	uint32_t textureId;
	PostProcessingEffect* effect;

private:
	HDRRendererComponent(class PostProcessingComponent* component);

protected:
	void onPreRender();
	void onPostRender();

friend class PostProcessingRenderer;
};

}  // namespace

#endif
