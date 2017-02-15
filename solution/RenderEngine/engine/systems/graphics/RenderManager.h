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
class TextureManager;
class Texture;

class Entity;
class DirectionalLightComponent;
class PointLightComponent;

class ColorRenderer;
class DiffuseTexturedRenderer;
class NormalMapRenderer;

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
	UPTR<TextureManager> textureManager;

	UPTR<ColorRenderer> colorRenderer;
	UPTR<DiffuseTexturedRenderer> diffuseRenderer;
	UPTR<NormalMapRenderer> normalMapRenderer;

	CameraComponent *mainCamera;

private:
	void addMesh(MeshComponent *mesh);
	void onBeforeMaterialChange(MeshComponent *mesh);
	void onAfterMaterialChange(MeshComponent *mesh);
	ColorRenderer *chooseRenderer(MeshComponent *mesh);

	void setMainCamera(CameraComponent *camera);
	CameraComponent *getMainCamera();

	void render();
	void renderCamera();

	static void DEBUG_drawTriangle();
	void clearBuffer();

	DirectionalLightComponent *addDirectionalLight(Entity *entity);
	PointLightComponent *addPointLight(Entity *entity);

	Texture *loadDiffuseTexture(const std::string &fileName);
	Texture *loadNormalTexture(const std::string &fileName);

friend class SceneManager;
friend class MeshComponent;
friend class RenderEngine;
friend class Material;
friend class DiffuseMaterialComponent;
friend class NormalMaterialComponent;
};

} // namespace
#endif
