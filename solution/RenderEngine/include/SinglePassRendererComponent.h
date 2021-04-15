#ifndef _SINGLE_PASS_RENDERER_COMPONENT_H_
#define _SINGLE_PASS_RENDERER_COMPONENT_H_

#include "APostProcessingRendererComponent.h"
#include "memory_aliases.h"

namespace sre
{

class SinglePassRendererComponent : public APostProcessingRendererComponent
{
private:
	class ShaderManager* shaderManager;
	class AGraphicsWrapper* graphicsWrapper;

	class Shader* shader;
	UPTR<struct GUIMeshData> meshData;
	uint32_t textureId;
	uint32_t fbo;

private:
	SinglePassRendererComponent(class PostProcessingComponent* component);

protected:
	void onPreRender();
	void onPostRender();

friend class PostProcessingRenderer;
};

}  // namespace

#endif
