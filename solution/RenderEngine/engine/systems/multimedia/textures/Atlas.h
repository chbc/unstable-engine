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
	std::unordered_map<char, UPTR<Rect>> uvs;

private:
	Atlas(Texture *texture);
	const Rect *getItem(char id);
	void loadUVs(const std::string &fontFileName);	// throws file not found
	void processLine(const std::string &input);
	void storeItems(std::unordered_map<std::string, int> &propertiesMap);

	void getProperties(const std::string &input, std::list<std::tuple<std::string, int>> &result);
	std::string getKey(const std::string &input);
	int getValue(const std::string &input);
	std::string findRegex(const std::string &input, const std::string &regex);

friend class AtlasManager;
};

} // namespace

#endif
