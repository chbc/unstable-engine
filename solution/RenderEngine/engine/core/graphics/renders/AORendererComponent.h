#ifndef _AO_RENDERER_COMPONENT_H_
#define _AO_RENDERER_COMPONENT_H_

#include "DiffuseRendererComponent.h"

namespace sre
{

class AORendererComponent : public DiffuseRendererComponent
{
protected:
	AORendererComponent(const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void setupShaderVariables(MeshComponent *mesh, uint32_t shaderProgram) override;
	void preDraw() override;
	void postDraw() override;

	friend class Renderer;
};

}  // namespace

#endif
