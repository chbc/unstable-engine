#ifndef _DIFFUSE_MATERIAL_COMPONENT_H_
#define _DIFFUSE_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"
#include <string>

namespace sre
{

class Texture;

class SRE_API DiffuseMaterialComponent : public AMaterialComponent
{
DECLARE_MATERIAL_COMPONENT()

private:
    class Texture* texture;
	
public:
	DiffuseMaterialComponent(Material *material, const std::string &fileName);

	uint32_t getTextureID(uint32_t index = 0) const;
};

} // namespace
#endif
