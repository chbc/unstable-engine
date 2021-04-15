#ifndef _A_MATERIAL_COMPONENT_H_
#define _A_MATERIAL_COMPONENT_H_

#include "core_defines.h"

namespace sre
{

class Material;

class SRE_API AMaterialComponent
{

protected:
    Material * material;

public:
    virtual ~AMaterialComponent() {}

protected:
	AMaterialComponent(Material *material) : material(material) {}
};

}

#endif
