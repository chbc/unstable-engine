#ifndef _ATLAS_H_
#define _ATLAS_H_

#include <engine/utils/math/Rect.h>
#include <engine/utils/memory_aliases.h>
#include "Texture.h"
#include <unordered_map>
#include <tuple>

namespace sre
{

class Atlas
{
private:
	Texture *texture;

	// <id, uv>
	std::unordered_map<std::string, Rect> uvs;

private:
	Atlas(Texture *texture);
	const Rect &getItem(const std::string &id);
	void loadUVs(const std::string &fontFileName);	// throws file not found
	void processLine(const std::string &input);
	void storeItems(std::unordered_map<std::string, std::string> &propertiesMap);

	void getProperties(const std::string &input, std::list<std::tuple<std::string, std::string>> &result);
	std::string findRegex(const std::string &input, const std::string &regex);

	uint32_t getTextureId();

friend class AtlasManager;
friend class GUITextComponent;
friend class GUIImageComponent;
};

} // namespace

#endif
