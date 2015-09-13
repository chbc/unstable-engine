#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

#include <engine/util/singleton_macros.h>
#include <vector>

namespace nodes
{
    class LightNode;
	class DirectionalLight;
	class PointLight;
}

using nodes::DirectionalLight;
using nodes::PointLight;
using nodes::LightNode;

namespace graphics
{

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

} // namespace graphics

#endif
