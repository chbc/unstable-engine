#ifndef _ATLAS_H_
#define _ATLAS_H_

#include <engine/utils/math/Rect.h>
#include "Texture.h"
#include <unordered_map>

namespace sre
{

class Atlas
{
private:
	Texture *texture;

	// <id, uv>
	std::unordered_map<std::string, Rect> uvs;
};

} // namespace

#endif
