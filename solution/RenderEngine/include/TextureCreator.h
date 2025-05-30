#pragma once

#include "ASingleton.h"
#include "memory_aliases.h"
#include "Texture.h"
#include "core_defines.h"

namespace sre
{

class AGraphicsWrapper;

class TextureCreator : public ASingleton
{
private:
    VECTOR_UPTR<Texture> createdTextures;
    AGraphicsWrapper *graphicsWrapper;
    uint32_t shadowIndex;
	uint32_t emptyIndex;

protected:
    void init() override;
    void preRelease() override;

public:
    Texture* createShadowTexture(uint32_t width, uint32_t height);
    Texture* createCubemapTexture(uint32_t width, uint32_t height);
	Texture* createEmptyTexture(uint32_t width, uint32_t height);
	Texture* createEmptyFloatingPointTexture(uint32_t width, uint32_t height);
    SRE_API void saveFramebuffer();
};

} // namespace
