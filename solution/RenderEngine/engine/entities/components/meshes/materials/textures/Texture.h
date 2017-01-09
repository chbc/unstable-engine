#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <stdint.h>

namespace sre
{

class Texture
{
private:
	uint32_t id;
	uint32_t width;
	uint32_t height;

public:
	Texture(uint32_t id, uint32_t width, uint32_t height);

	uint32_t getId();
	uint32_t getWidth();
	uint32_t getHeight();
};

} // namespace

#endif
