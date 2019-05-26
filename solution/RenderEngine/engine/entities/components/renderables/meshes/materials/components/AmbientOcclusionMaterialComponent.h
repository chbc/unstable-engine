#ifndef _AMBIENT_OCCLUSION_MATERIAL_COMPONENT_H_
#define _AMBIENT_OCCLUSION_MATERIAL_COMPONENT_H_

#include "NormalMaterialComponent.h"

namespace sre
{

class SRE_API AmbientOcclusionMaterialComponent : public NormalMaterialComponent
{
public:
	AmbientOcclusionMaterialComponent(Material *material, const std::string &fileName);

	void loadTexture(const std::string &fileName) override;
};

} // namespace

#endif
