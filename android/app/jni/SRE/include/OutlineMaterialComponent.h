#ifndef _OUTLINE_MATERIAL_COMPONENT_H_
#define _OUTLINE_MATERIAL_COMPONENT_H_

#include "ColorMaterialComponent.h"

namespace sre
{

class SRE_API OutlineMaterialComponent : public ColorMaterialComponent
{
public:
	OutlineMaterialComponent(class Material *material);
};

} // namespace
#endif
