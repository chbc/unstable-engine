#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <engine/core/singletonsManager/ASingleton.h>
#include <engine/utils/memory_aliases.h>
#include "Texture.h"

namespace sre
{

class AGraphicsWrapper;

/*!
	Class to manage low level texturing.
*/
class TextureManager : public ASingleton
{
private:
    VECTOR_UPTR<Texture> textures;
    AGraphicsWrapper *graphicsWrapper;

protected:
    void init() override;
    void release() override;

private:
    Texture *loadGUITexture(const std::string &fileName);
    Texture *loadDiffuseTexture(const std::string &fileName);
    Texture *loadNormalTexture(const std::string &fileName);
    Texture *loadSpecularTexture(const std::string &fileName);
    Texture *loadAOTexture(const std::string &fileName);
    Texture *loadShadowTexture(uint32_t width, uint32_t height);
    Texture *loadTexture(const std::string &fileName, EMaterialMap::Type mapType);

    Texture *loadExistingTexture(const std::string &fileName, EMaterialMap::Type mapType);
    void deleteTexture(uint32_t id);

public:
    ~TextureManager();

friend class RenderManager;
friend class SingletonsManager;
friend class LightManager;
};

} // namespace
#endif
