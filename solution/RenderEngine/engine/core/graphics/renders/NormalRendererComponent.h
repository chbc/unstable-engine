#ifndef _NORMAL_RENDERER_COMPONENT_H_
#define _NORMAL_RENDERER_COMPONENT_H_

#include "DiffuseRendererComponent.h"

namespace sre
{

class NormalRendererComponent : public DiffuseRendererComponent
{
protected:
	NormalRendererComponent(const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void setupShaderVariables(MeshComponent *mesh, uint32_t shaderProgram) override;
	void preDraw() override;
	void postDraw() override;

friend class Renderer;
};

} // namespace

#endif
