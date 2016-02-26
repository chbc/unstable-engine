#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "LightNode.h"

namespace sre
{

class LightManager;

class PointLight : public LightNode
{
	private:
		PointLight();

	public:
		void setPosition(const Vector &position);
		ELightType getType();

	friend class LightManager;
};

} // namespace

#endif
