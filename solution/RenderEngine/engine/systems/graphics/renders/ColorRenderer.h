#ifndef _COLOR_RENDERER_H_
#define _COLOR_RENDERER_H_

#include <engine/utils/memory_aliases.h>
#include <glm/vec3.hpp>
#include <list>

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
	std::list<MeshComponent *> meshes;

protected:
	uint32_t shaderProgram;
	UPTR<ShaderManager> shaderManager;
	SPTR<AGraphicsWrapper> graphicsWrapper;

public:
	~ColorRenderer();

protected:
	ColorRenderer(const SPTR<AGraphicsWrapper> &graphicsWrapper);

	virtual void loadShader();
	virtual void setupMaterial(MeshComponent *mesh);
	virtual void drawMesh(MeshComponent *mesh);

private:
	void addMesh(MeshComponent *mesh);
	void removeMesh(MeshComponent *mesh);
	void createVBO(MeshComponent *mesh);	// ###
	void render(MatrixManager *matrixManager, LightManager *lightManager, const glm::vec3 &cameraPosition);
	bool contains(MeshComponent *mesh);
	inline bool hasMeshes() { return this->meshes.size() > 0; }

friend class RenderManager;
};

} // namespace

#endif
