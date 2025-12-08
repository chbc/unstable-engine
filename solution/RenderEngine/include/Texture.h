#pragma once

#include "ETextureMap.h"
#include "core_defines.h"

#include <stdint.h>
#include <string>

namespace sre
{

class SRE_API Texture
{
private:
	uint32_t id{ 0 };
	uint32_t width{ 0 };
	uint32_t height{ 0 };
	ETextureMap::Type mapType{ ETextureMap::GUI };
	uint32_t unit{ 0 };
	std::string filePath;
	bool flipGreenChannel{ false };

public:
	Texture(uint32_t id, uint32_t width, uint32_t height, ETextureMap::Type mapType, std::string filePath, uint32_t unitOffset = 0);

	uint32_t& getId();
	uint32_t getWidth();
	uint32_t getHeight();
	ETextureMap::Type getMapType();
    uint32_t getUnit();
	const std::string &getFilePath();
	bool getFlipGreenChannel() const;
	void setFlipGreenChannel(bool newValue);

friend class AssetsManager;
};

} // namespace
