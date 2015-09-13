#ifndef _DIRECTIONAL_LIGHT_H_
#define _DIRECTIONAL_LIGHT_H_

#include "LightNode.h"

namespace graphics
{
    class LightManager;
}

namespace nodes
{

class DirectionalLight : public LightNode
{
	private:
		DirectionalLight();

	public:
		void setDirection(const Vector &direction);
		ELightType getType();

	friend class graphics::LightManager;
};

} // namespace nodes

#endif
