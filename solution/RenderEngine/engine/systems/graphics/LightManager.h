#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include <engine/utils/memory_aliases.h>
#include <engine/entities/components/lights/DirectionalLightComponent.h>
#include <engine/entities/components/lights/PointLightComponent.h>

namespace sre
{
class Entity;
class ShaderManager;

/*!
	Class to manage low level lighting.
*/
class LightManager
{
private:
    std::vector<DirectionalLightComponent *> directionalLights;
	std::vector<PointLightComponent *> pointLights;

	glm::vec3 ambientLightColor;

public:
	~LightManager();

	void setAmbientLightColor(const glm::vec3 &ambientLightColor);

private:
	LightManager();

	DirectionalLightComponent *addDirectionalLight(Entity *entity);
	PointLightComponent *addPointLight(Entity *entity);

	void setupLights(ShaderManager *shaderManager, uint32_t program);
	void setupDirectionalLights(ShaderManager *shaderManager, uint32_t program);
	void setupPointLights(ShaderManager *shaderManager, uint32_t program);

	friend class RenderManager;
	friend class ColorRenderer;
};

} // namespace

#endif
