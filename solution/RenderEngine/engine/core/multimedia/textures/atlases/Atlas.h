#ifndef _ATLAS_H_
#define _ATLAS_H_

#include <engine/utils/math/Rect.h>
#include <engine/utils/memory_aliases.h>
#include "../Texture.h"
#include <unordered_map>
#include <tuple>

namespace sre
{

namespace keys
{
	static const std::string ID		= "id";
	static const std::string X		= "x";
	static const std::string Y		= "y";
	static const std::string WIDTH	= "width";
	static const std::string HEIGHT	= "height";
}

struct AtlasItem
{
	Rect uv;
	glm::vec2 pixelSize;
	glm::vec2 normalizedSize;

	AtlasItem(Rect uv, glm::vec2 pixelSize, glm::vec2 normalizedSize)
		: uv(uv), pixelSize(pixelSize), normalizedSize(normalizedSize) { }
};

class Atlas
{
private:
	Texture *texture;

	// <id, item>
	std::unordered_map<std::string, UPTR<AtlasItem>> items;

protected:
	Atlas(Texture *texture);

	virtual bool checkProperties(const std::unordered_map<std::string, std::string> &properties);
	virtual AtlasItem *createItem(std::unordered_map<std::string, std::string> &propertiesMap);
	virtual uint16_t getMinItems();
	float getValue(std::unordered_map<std::string, std::string> &propertiesMap, const std::string &key);

private:
	const AtlasItem *getItem(const std::string &id);
	void load(const std::string &fontFileName);	// throws file not found
	void processLine(const std::string &input);
	void getProperties(const std::string &input, std::unordered_map<std::string, std::string> &result);

	uint32_t getTextureId();

friend class AtlasManager;
friend class GUITextComponent;
friend class GUIImageComponent;
};

} // namespace

#endif
