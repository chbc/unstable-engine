#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <stdint.h>
#include "EMaterialMap.h"
#include <string>

namespace sre
{

class Texture
{
private:
	uint32_t id;
	uint32_t width;
	uint32_t height;
	EMaterialMap::Type mapType;
    uint32_t unit;
	std::string fileName;

public:
	Texture(uint32_t id, uint32_t width, uint32_t height, EMaterialMap::Type mapType, std::string fileName, uint32_t unitOffset = 0);

	uint32_t getId();
	uint32_t getWidth();
	uint32_t getHeight();
	EMaterialMap::Type getMapType();
    uint32_t getUnit();
	const std::string &getFileName();
};

} // namespace

#endif
