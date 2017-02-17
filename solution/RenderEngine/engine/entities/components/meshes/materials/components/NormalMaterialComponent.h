#ifndef _NORMAL_MATERIAL_COMPONENT_H_
#define _NORMAL_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"
#include <engine/utils/memory_aliases.h>
#include "../textures/Texture.h"

namespace sre
{

class NormalMaterialComponent : public AMaterialComponent
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
