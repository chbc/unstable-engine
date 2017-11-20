#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include <engine/entities/components/lights/DirectionalLightComponent.h>
#include <engine/entities/components/lights/PointLightComponent.h>
#include <engine/core/singletonsManager/ASingleton.h>

#include <vector>

namespace sre
{

class Entity;
class ShaderManager;

/*!
	Class to manage low level lighting.
*/
class LightManager : public ASingleton
{
private:
    std::vector<DirectionalLightComponent *> directionalLights;
	std::vector<PointLightComponent *> pointLights;

	glm::vec3 ambientLightColor;

public:
	void setAmbientLightColor(const glm::vec3 &ambientLightColor);

private:
	LightManager();

	DirectionalLightComponent *addDirectionalLight(Entity *entity);
	PointLightComponent *addPointLight(Entity *entity);

	void setupLights(ShaderManager *shaderManager, uint32_t program);
	void setupDirectionalLights(ShaderManager *shaderManager, uint32_t program);
	void setupPointLights(ShaderManager *shaderManager, uint32_t program);

friend class RenderManager;
friend class SingletonsManager;

friend class ColorRenderer;
	
friend class Renderer;
};

} // namespace

#endif
