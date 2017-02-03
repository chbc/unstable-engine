#ifndef _DIFFUSE_TEXTURED_RENDERER_H_
#define _DIFFUSE_TEXTURED_RENDERER_H_

#include "ColorRenderer.h"

namespace sre
{

class MatrixManager;
class LightManager;

class DiffuseTexturedRenderer : public ColorRenderer
{
protected:
	uint32_t loadShader(ShaderManager *shaderManager);
	void drawMesh(MeshComponent *mesh) override;
};

} // namespace

#endif
