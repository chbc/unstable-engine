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

private:
	SinglePassRendererComponent(class PostProcessingComponent* component);

protected:
	void onPostRender(uint32_t targetFBO) override;

friend class PostProcessingRenderer;
};

}  // namespace

#endif
