#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "LightNode.h"

namespace graphics
{
    class LightManager;
}

namespace nodes
{

class PointLight : public LightNode
{
	private:
		PointLight();

	public:
		void setPosition(const Vector &position);
		ELightType getType();

	friend class graphics::LightManager;
};

} // namespace nodes

#endif
