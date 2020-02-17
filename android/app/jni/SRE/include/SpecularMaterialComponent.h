#ifndef _SPECULAR_MATERIAL_COMPONENT_H_
#define _SPECULAR_MATERIAL_COMPONENT_H_

#include "NormalMaterialComponent.h"

namespace sre
{

class SRE_API SpecularMaterialComponent : public NormalMaterialComponent
{
public:
	SpecularMaterialComponent(Material *material, const std::string &fileName);

	void loadTexture(const std::string &fileName) override;
};

} // namespace

#endif
