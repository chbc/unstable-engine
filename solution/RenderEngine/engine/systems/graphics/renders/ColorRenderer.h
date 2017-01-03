#ifndef _COLOR_RENDERER_H_
#define _COLOR_RENDERER_H_

#include <vector>

namespace sre
{

class MeshComponent;
class MatrixManager;
class AGraphicsWrapper;
class MatrixManager;
class ShaderManager;

class ColorRenderer
{
private:
	std::vector<MeshComponent *> meshes;

public:
	~ColorRenderer();

private:
	ColorRenderer();

	void addMesh(MeshComponent *mesh);
	void render(MatrixManager *matrixManager, ShaderManager *shaderManager, AGraphicsWrapper *graphicsWrapper);

friend class RenderManager;
};

}

#endif
