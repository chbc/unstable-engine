#ifndef _DIRECTIONAL_LIGHT_H_
#define _DIRECTIONAL_LIGHT_H_

#include "LightNode.h"

namespace sre
{

class LightManager;

class DirectionalLight : public LightNode
{
	private:
		DirectionalLight();

	public:
		void setDirection(const Vector &direction);
		ELightType getType();

	friend class LightManager;
};

} // namespace
#endif
