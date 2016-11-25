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
class LightManager;

class Entity;
class DirectionalLightComponent;
class PointLightComponent;

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
*/

	SPTR<AGraphicsWrapper> graphicsWrapper;
	UPTR<ShaderManager> shaderManager;
	UPTR<MatrixManager> matrixManager;
	UPTR<LightManager> lightManager;

private:
	void render(MeshComponent *mesh);

	static void DEBUG_drawTriangle();
	void clearBuffer();

/* ###
	void applyMaterial(Material *material, bool receiveLight);
	void applyMaterial(DiffuseMaterial *material, std::vector<VertexData> *vertexData, bool receiveLight);
*/

	// ### void releaseMaterial(Material *material);

	void renderCamera(const glm::vec3 &position, const glm::vec3 &lookTarget, const glm::vec3 &up);

/* ###
	Texture *loadTexture(const std::string &fileName);
*/
	unsigned int loadShader(const std::string &vertFile, const std::string &fragFile);

	void createBufferObject(MeshComponent *mesh);

	DirectionalLightComponent *addDirectionalLight(Entity *entity);
	PointLightComponent *addPointLight(Entity *entity);

// ### friend class SceneManager;
friend class MeshComponent;
friend class RenderEngine;
};

} // namespace
#endif
