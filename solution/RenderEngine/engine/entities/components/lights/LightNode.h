#ifndef _LIGHT_NODE_H_
#define _LIGHT_NODE_H_

#include <engine/entities/Node.h>
#include <string.h>

enum ELightType
{
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT = 1
};

namespace sre
{

class LightManager;

/*!
	Base class to handle lighting.
*/
class LightNode : public Node
{
	private:
		Vector color;

	protected:
		Vector posDir;
		// ### float range;

		LightNode();

	public:
        void setColor(const Vector &color);
        virtual ELightType getType() =0;

    friend class LightManager;
};

} // namespace

#endif
