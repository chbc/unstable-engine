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
class CameraComponent;
class AGraphicsWrapper;
class MatrixManager;
class ShaderManager;
class LightManager;

class Entity;
class DirectionalLightComponent;
class PointLightComponent;

class ColorRenderer;

/* ###
class VertexData;
class RenderableNode;
class LightNode;
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
	UPTR<MatrixManager> matrixManager;
	UPTR<LightManager> lightManager;

	UPTR<ColorRenderer> colorRenderer;

	CameraComponent *mainCamera;

private:
	void addMesh(MeshComponent *mesh);
	void setMainCamera(CameraComponent *camera);
	CameraComponent *getMainCamera();

	void render();
	void renderCamera();

	static void DEBUG_drawTriangle();
	void clearBuffer();

/* ###
	void applyMaterial(Material *material, bool receiveLight);
	void applyMaterial(DiffuseMaterial *material, std::vector<VertexData> *vertexData, bool receiveLight);
*/

	// ### void releaseMaterial(Material *material);

/* ###
	Texture *loadTexture(const std::string &fileName);
*/
	void createVBO(MeshComponent *mesh);

	DirectionalLightComponent *addDirectionalLight(Entity *entity);
	PointLightComponent *addPointLight(Entity *entity);

friend class SceneManager;
friend class MeshComponent;
friend class RenderEngine;
friend class Material;
};

} // namespace
#endif
