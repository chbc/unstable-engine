#ifndef _COLOR_RENDERER_H_
#define _COLOR_RENDERER_H_

#include <engine/utils/memory_aliases.h>
#include <vector>

namespace sre
{

class MeshComponent;
class MatrixManager;
class AGraphicsWrapper;
class MatrixManager;
class ShaderManager;
class AGraphicsWrapper;

class ColorRenderer
{
private:
	std::vector<MeshComponent *> meshes;
	UPTR<ShaderManager> shaderManager;
	SPTR<AGraphicsWrapper> graphicsWrapper;

	uint32_t shaderPorgram;
	int vertexAttribLocation;
	int normalAttribLocation;

public:
	~ColorRenderer();

private:
	ColorRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void addMesh(MeshComponent *mesh);
	void createVBO(MeshComponent *mesh);	// ###
	uint32_t loadShader(const std::string &vertFile, const std::string &fragFile);
	void render(MatrixManager *matrixManager, AGraphicsWrapper *graphicsWrapper);

friend class RenderManager;
};

}

#endif
