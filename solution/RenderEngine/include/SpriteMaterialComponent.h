#ifndef _SPRITE_MATERIAL_COMPONENT_H_
#define _SPRITE_MATERIAL_COMPONENT_H_

#include "AMaterialCOmponent.h"
#include <string>

namespace sre
{
	
class SRE_API SpriteMaterialComponent : public AMaterialComponent
{
private:
	class Texture* texture;
	
public:
	SpriteMaterialComponent(Material* material, const std::string& fileName);

	uint32_t getTextureID() const;
};
	
} // namespace

#endif
