#ifndef _NORMAL_MATERIAL_COMPONENT_H_
#define _NORMAL_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"
#include <string>

namespace sre
{

class SRE_API NormalMaterialComponent : public AMaterialComponent
{
private:
	class Texture* texture;

public:
	NormalMaterialComponent(Material *material, const std::string &fileName);

	uint32_t getTextureID() const;
};

} // namespace

#endif
