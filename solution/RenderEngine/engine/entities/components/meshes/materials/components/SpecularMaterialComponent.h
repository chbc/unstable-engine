#ifndef _SPECULAR_MATERIAL_COMPONENT_H_
#define _SPECULAR_MATERIAL_COMPONENT_H_

#include "NormalMaterialComponent.h"

namespace sre
{

class SpecularMaterialComponent : public NormalMaterialComponent
{
public:
	SpecularMaterialComponent(Material *material, const std::string &fileName);
};

} // namespace

#endif
