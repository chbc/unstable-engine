#ifndef _AO_MAP_RENDERER_H_
#define _AO_MAP_RENDERER_H_

#include "ColorRenderer.h"

namespace sre
{

class AOMapRenderer : public ColorRenderer
{
protected:
	AOMapRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void loadShader() override;
	void setupMaterial(MeshComponent *mesh) override;
	void drawMesh(MeshComponent *mesh) override;

	friend class RenderManager;
};

} // namespace

#endif
