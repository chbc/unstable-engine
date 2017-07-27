#ifndef _ATLAS_H_
#define _ATLAS_H_

#include <engine/utils/math/Rect.h>
#include <engine/utils/memory_aliases.h>
#include "Texture.h"
#include <unordered_map>

namespace sre
{

class Atlas
{
private:
	Texture *texture;
	// <id, uv>
	std::unordered_map<char, UPTR<Rect>> uvs;

private:
	Atlas(Texture *texture);
	const Rect *getItem(char id);
	void loadUVs(const std::string &fontFileName);	// throws file not found
	void parse(const std::string &input);

friend class AtlasManager;
};

} // namespace

#endif
