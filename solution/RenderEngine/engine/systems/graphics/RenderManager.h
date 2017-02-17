#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include <engine/utils/singleton_macros.h>
#include <glm/vec3.hpp>

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

/*!
	Singleton Class to handle renders
*/
class RenderManager
{
DECLARE_SINGLETON(RenderManager);

private:
	SPTR<AGraphicsWrapper> graphicsWrapper;
	UPTR<MatrixManager> matrixManager;
	UPTR<LightManager> lightManager;
	UPTR<TextureManager> textureManager;

	UPTR<ColorRenderer> colorRenderer;
	UPTR<ColorRenderer> diffuseRenderer;
	UPTR<ColorRenderer> normalMapRenderer;
	UPTR<ColorRenderer> specularMapRenderer;
	UPTR<ColorRenderer> aoMapRenderer;

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
	Texture *loadSpecularTexture(const std::string &fileName);
	Texture *loadAOTexture(const std::string &fileName);

friend class SceneManager;
friend class MeshComponent;
friend class RenderEngine;
friend class Material;
friend class DiffuseMaterialComponent;
friend class NormalMaterialComponent;
friend class SpecularMaterialComponent;
friend class AmbientOcclusionMaterialComponent;
};

} // namespace
#endif
