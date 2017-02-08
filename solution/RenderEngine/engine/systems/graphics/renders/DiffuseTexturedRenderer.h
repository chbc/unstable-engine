#ifndef _DIFFUSE_TEXTURED_RENDERER_H_
#define _DIFFUSE_TEXTURED_RENDERER_H_

#include "ColorRenderer.h"

namespace sre
{

class DiffuseTexturedRenderer : public ColorRenderer
{
protected:
	DiffuseTexturedRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void loadShader() override;
	void drawMesh(MeshComponent *mesh) override;

friend class RenderManager;
};

} // namespace

#endif
