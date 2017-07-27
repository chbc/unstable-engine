#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <engine/utils/memory_aliases.h>
#include "Texture.h"

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

	Texture *loadGUITexture(const std::string &fileName);
	Texture *loadDiffuseTexture(const std::string &fileName);
	Texture *loadNormalTexture(const std::string &fileName);
	Texture *loadSpecularTexture(const std::string &fileName);
	Texture *loadAOTexture(const std::string &fileName);
	Texture *loadTexture(const std::string &fileName, EMaterialMap::Type mapType);

	Texture *loadExistingTexture(const std::string &fileName, EMaterialMap::Type mapType);
	void deleteTexture(uint32_t id);

public:
	~TextureManager();

friend class RenderManager;
};

} // namespace
#endif
