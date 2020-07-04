#ifndef _NORMAL_MATERIAL_COMPONENT_H_
#define _NORMAL_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"
#include "memory_aliases.h"
#include "Texture.h"

namespace sre
{

class SRE_API NormalMaterialComponent : public AMaterialComponent
{
protected:
	UPTR<Texture> texture;

public:
	NormalMaterialComponent(Material *material, const std::string &fileName);

	virtual void loadTexture(const std::string &fileName);
	uint32_t getTextureID();
};

} // namespace

#endif