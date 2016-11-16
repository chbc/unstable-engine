#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include <engine/utils/singleton_macros.h>
#include <glm/vec3.hpp>

/* ###
#include "TextureManager.h"
#include "ShaderManager.h"
#include "LightManager.h"
*/

namespace sre
{
class MeshComponent;
class AGraphicsWrapper;
class MatrixManager;
class ShaderManager;

/* ###
class VertexData;
class RenderableNode;
class LightNode;
class Material;
class DiffuseMaterial;
class SceneManager;
*/

/*!
	Singleton Class for low level rendering
*/
class RenderManager
{
DECLARE_SINGLETON(RenderManager);

private:
/* ###
	TextureManager *textureManager;
	LightManager *lightManager;
*/

	SPTR<AGraphicsWrapper> graphicsWrapper;
	UPTR<ShaderManager> shaderManager;
	UPTR<MatrixManager> matrixManager;

private:
	static void DEBUG_drawTriangle();
	void clearBuffer();

/* ###
	void applyMaterial(Material *material, bool receiveLight);
	void applyMaterial(DiffuseMaterial *material, std::vector<VertexData> *vertexData, bool receiveLight);
*/

	void drawMesh(MeshComponent *mesh);
	// ### void releaseMaterial(Material *material);

	void renderCamera(const glm::vec3 &position, const glm::vec3 &lookTarget, const glm::vec3 &up);

/* ###
	Texture *loadTexture(const std::string &fileName);
*/
	unsigned int loadShader(const std::string &vertFile, const std::string &fragFile);

	void createBufferObject(MeshComponent *mesh);

/* ###
	DirectionalLight *addDirectionalLight();
	PointLight *addPointLight();
	void render(const std::vector<RenderableNode *> &renderableNodes);
*/

// ### friend class SceneManager;
friend class MeshComponent;
friend class RenderEngine;
};

} // namespace
#endif
