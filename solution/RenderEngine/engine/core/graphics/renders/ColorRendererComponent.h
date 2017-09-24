#ifndef _COLOR_RENDERER_COMPONENT_H_
#define _COLOR_RENDERER_COMPONENT_H_

#include <engine/utils/memory_aliases.h>

namespace sre
{

class ShaderManager;
class AGraphicsWrapper;
class MeshComponent;

class ColorRendererComponent
{
protected:
	SPTR<ShaderManager> shaderManager;
	SPTR<AGraphicsWrapper> graphicsWrapper;

protected:
	ColorRendererComponent(const SPTR<ShaderManager> &shaderManager, const SPTR<AGraphicsWrapper> &graphicsWrapper);

	virtual void setupShaderVariables(MeshComponent *mesh, uint32_t shaderProgram);
	virtual void preDraw();
	virtual void postDraw();

friend class Renderer;
};

} // namespace

#endif
