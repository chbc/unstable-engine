#pragma once

#include "ASingleton.h"
#include "memory_aliases.h"
#include "Texture.h"
#include "core_defines.h"

#include <unordered_map>
#include <queue>

namespace sre
{

class AGraphicsWrapper;

class TextureCreator : public ASingleton
{
private:
    // <id, texture>
    std::unordered_map<uint32_t, UPTR<Texture>> createdTextures;
    AGraphicsWrapper* graphicsWrapper{ nullptr };
	uint32_t emptyIndex;

protected:
    void init() override;
    void preRelease() override;

public:
    Texture* createDirectionalShadowTexture(uint32_t width, uint32_t height, uint32_t& resultFbo);
    Texture* createPointShadowTexture(uint32_t width, uint32_t height, uint32_t& resultFbo);
	Texture* createEmptyTexture(uint32_t width, uint32_t height);
	Texture* createEmptyFloatingPointTexture(uint32_t width, uint32_t height);
	void deleteTexture(uint32_t id);
    SRE_API void saveFramebuffer();
};

} // namespace
