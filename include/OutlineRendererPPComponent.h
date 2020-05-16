#ifndef _OUTLINE_RENDERER_PP_COMPONENT_H_
#define _OUTLINE_RENDERER_PP_COMPONENT_H_

#include "APostProcessingRendererComponent.h"
#include "memory_aliases.h"

namespace sre
{

class OutlineRendererPPComponent : public APostProcessingRendererComponent
{
private:
	class ShaderManager* shaderManager;
	class AGraphicsWrapper* graphicsWrapper;
	UPTR<struct GUIMeshData> meshData;

	class Shader* outlineShader;
	class Shader* combineShader;
	
	uint32_t initialPassTextureId;
	uint32_t colorSourceTextureId;
	uint32_t outlineTextureId;

	uint32_t initialPassFBO;
	uint32_t outlinePassFBO;

private:
	OutlineRendererPPComponent(class PostProcessingComponent* component);

protected:
	void onPreRender();
	void onPostRender();

friend class PostProcessingRenderer;
};

}  // namespace

#endif
