#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <engine/utils/singleton_macros.h>
#include <engine/entities/renderables/materials/textures/Texture.h>
#include <string>

namespace sre
{

/*!
	Class to manage low level texturing.
*/
class TextureManager
{
	DECLARE_SINGLETON(TextureManager);

	public:
		Texture *loadTexture(const std::string &fileName);
		void deleteTexture(unsigned int id);
};

} // namespace
#endif
