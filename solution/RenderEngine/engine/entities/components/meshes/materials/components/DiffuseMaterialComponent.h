#ifndef _DIFFUSE_MATERIAL_COMPONENT_H_
#define _DIFFUSE_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"
#include <engine/utils/memory_aliases.h>
#include "../textures/Texture.h"

namespace sre
{

class DiffuseMaterialComponent : public AMaterialComponent
{
private:
    VECTOR_UPTR<Texture> textures;

public:
	DiffuseMaterialComponent(Material *material, const std::string &fileName);

	void loadTexture(const std::string &fileName);
	unsigned int getTextureID(uint32_t index = 0);
};

} // namespace
#endif
