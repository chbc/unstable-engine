#ifndef _COLOR_RENDERER_COMPONENT_H_
#define _COLOR_RENDERER_COMPONENT_H_

#include <stdint.h>

namespace sre
{

class ShaderManager;
class AGraphicsWrapper;
class MeshComponent;

class ColorRendererComponent
{
protected:
	ShaderManager *shaderManager;
	AGraphicsWrapper *graphicsWrapper;

protected:
	ColorRendererComponent(ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

	virtual void setupShaderVariables(MeshComponent *mesh, uint32_t shaderProgram);
	virtual void preDraw();
	virtual void postDraw();

friend class Renderer;
};

} // namespace

#endif
