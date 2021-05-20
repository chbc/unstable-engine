#ifndef _DOF_RENDERER_COMPONENT_H_
#define _DOF_RENDERER_COMPONENT_H_

#include "APostProcessingRendererComponent.h"
#include "memory_aliases.h"

namespace sre
{

class DOFRendererComponent : public APostProcessingRendererComponent
{
private:
	class ShaderManager* shaderManager;
	class AGraphicsWrapper* graphicsWrapper;
	UPTR<struct GUIMeshData> meshData;

	class Shader* depthShader;
	class Shader* shader;
	
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

#endif
