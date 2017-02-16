#ifndef _SPECULAR_MAP_RENDERER_H_
#define _SPECULAR_MAP_RENDERER_H_

#include "ColorRenderer.h"

namespace sre
{

class SpecularMapRenderer : public ColorRenderer
{
protected:
	SpecularMapRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void loadShader() override;
	void setupMaterial(MeshComponent *mesh) override;
	void drawMesh(MeshComponent *mesh) override;

	friend class RenderManager;
};

} // namespace

#endif

