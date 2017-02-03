#ifndef _COLOR_RENDERER_H_
#define _COLOR_RENDERER_H_

#include <engine/utils/memory_aliases.h>
#include <glm/vec3.hpp>
#include <vector>

namespace sre
{

class MeshComponent;
class MatrixManager;
class AGraphicsWrapper;
class ShaderManager;
class LightManager;

class ColorRenderer
{
private:
	std::vector<MeshComponent *> meshes;
	UPTR<ShaderManager> shaderManager;

	uint32_t shaderProgram;

protected:
	SPTR<AGraphicsWrapper> graphicsWrapper;

public:
	~ColorRenderer();

protected:
	virtual uint32_t loadShader(ShaderManager *shaderManager);
	virtual void setupMaterial(MeshComponent *mesh);
	virtual void drawMesh(MeshComponent *mesh);

private:
	ColorRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper);

	void addMesh(MeshComponent *mesh);
	void createVBO(MeshComponent *mesh);	// ###
	void render(MatrixManager *matrixManager, LightManager *lightManager, const glm::vec3 &cameraPosition);

friend class RenderManager;
};

} // namespace

#endif
