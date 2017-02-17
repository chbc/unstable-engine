#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <engine/utils/memory_aliases.h>
#include <engine/entities/components/meshes/materials/textures/Texture.h>

namespace sre
{

class AGraphicsWrapper;

/*!
	Class to manage low level texturing.
*/
class TextureManager
{
private:
	VECTOR_UPTR<Texture> textures;

	AGraphicsWrapper *graphicsWrapper;

private:
	TextureManager(AGraphicsWrapper *graphicsWrapper);

	Texture *loadDiffuseTexture(const std::string &fileName);
	Texture *loadNormalTexture(const std::string &fileName);
	Texture *loadSpecularTexture(const std::string &fileName);
	Texture *loadAOTexture(const std::string &fileName);
	Texture *loadTexture(const std::string &fileName, uint32_t unit);
	void deleteTexture(uint32_t id);

public:
	~TextureManager();

friend class RenderManager;
};

} // namespace
#endif
