#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include <engine/utils/singleton_macros.h>
#include <vector>

namespace sre
{
	class LightNode;
	class DirectionalLight;
	class PointLight;

/*!
	Class to manage low level lighting.
*/
class LightManager
{
	DECLARE_SINGLETON(LightManager);

	private:
        std::vector<LightNode *> lightNodes;

		DirectionalLight *addDirectionalLight();
		PointLight *addPointLight();

		void setupLights(unsigned int program);

	friend class RenderManager;
};

} // namespace

#endif
