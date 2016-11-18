#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include <engine/utils/memory_aliases.h>
#include <engine/entities/components/lights/DirectionalLightComponent.h>
#include <engine/entities/components/lights/PointLightComponent.h>

namespace sre
{
class Entity;

/*!
	Class to manage low level lighting.
*/
class LightManager
{
private:
    VECTOR_UPTR<ALightComponent> lightComponents;

	DirectionalLightComponent *addDirectionalLight(Entity *entity);
	PointLightComponent *addPointLight(Entity *entity);

public:
	~LightManager();

private:
	LightManager() {}
	void setupLights(unsigned int program);

	friend class RenderManager;
};

} // namespace

#endif
