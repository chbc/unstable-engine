#ifndef _DIFFUSE_MATERIAL_COMPONENT_H_
#define _DIFFUSE_MATERIAL_COMPONENT_H_

#include "AMaterialComponent.h"
#include <engine/utils/memory_aliases.h>

namespace sre
{

class Texture;

class DiffuseMaterialComponent : public AMaterialComponent
{
private:
    VECTOR_UPTR<Texture> textures; // ### TEXTURE MANAGER JÁ É O DONO

public:
	DiffuseMaterialComponent(Material *material, const std::string &fileName);

	void loadTexture(const std::string &fileName);
	uint32_t getTextureID(uint32_t index = 0);
};

} // namespace
#endif
