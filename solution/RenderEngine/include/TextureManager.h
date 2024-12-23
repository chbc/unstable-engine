#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "ASingleton.h"
#include "memory_aliases.h"
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
    uint32_t shadowIndex;
	uint32_t emptyIndex;

protected:
    void init() override;
    void preRelease() override;

private:
    Texture* loadGUITexture(const std::string &fileName);
    Texture* loadDiffuseTexture(const std::string &fileName);
    Texture* loadNormalTexture(const std::string &fileName);
    Texture* loadSpecularTexture(const std::string &fileName);
    Texture* loadAOTexture(const std::string &fileName);
    Texture* createShadowTexture(uint32_t width, uint32_t height);
    Texture* createCubemapTexture(uint32_t width, uint32_t height);
	Texture* createEmptyTexture(uint32_t width, uint32_t height);
	Texture* createEmptyFloatingPointTexture(uint32_t width, uint32_t height);
    Texture* loadTexture(const std::string &fileName, ETextureMap::Type mapType);

    Texture* loadExistingTexture(const std::string &fileName, ETextureMap::Type mapType);
    void deleteTexture(uint32_t id);

friend class RenderManager;
friend class SingletonsManager;
friend class ShadowRenderer;
friend class PostProcessingRenderer;
friend class BloomRendererComponent;
friend class SinglePassRendererComponent;
friend class HDRRendererComponent;
friend class DOFRendererComponent;
friend class OutlineRendererPPComponent;
friend class GUIImageComponent;
friend class GUITextComponent;
friend class ABaseTextureMaterialComponent;
friend class AtlasManager;
friend class GUITextComponent;
friend class EditorSceneViewport;
friend class EditorFileBrowser;
};

} // namespace
#endif
