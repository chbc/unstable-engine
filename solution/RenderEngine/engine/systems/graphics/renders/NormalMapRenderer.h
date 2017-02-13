#ifndef _NORMAL_MAP_RENDERER_H_
#define _NORMAL_MAP_RENDERER_H_

#include "ColorRenderer.h"

namespace sre
{

class NormalMapRenderer : public ColorRenderer
{
protected:
	NormalMapRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void loadShader() override;
	void drawMesh(MeshComponent *mesh) override;

friend class RenderManager;
};

} // namespace

#endif
