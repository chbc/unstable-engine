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
	void drawMesh(MeshComponent *mesh) override;
};

} // namespace

#endif
