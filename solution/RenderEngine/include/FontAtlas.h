#pragma once

#include "Atlas.h"

namespace sre
{

namespace keys
{
	static const std::string X_OFFSET	= "xoffset";
	static const std::string Y_OFFSET	= "yoffset";
	static const std::string X_ADVANCE	= "xadvance";
}

struct FontItem : public AtlasItem
{
	glm::vec2 offset{ 0.0f };
	float xAdvance{ 0.0f };

	FontItem(AtlasItem *baseItem, glm::vec2 offset, float xAdvance) 
		: AtlasItem(baseItem->uv, baseItem->pixelSize, baseItem->normalizedSize), offset(offset), xAdvance(xAdvance) 
	{
		delete baseItem;
	}
};

class FontAtlas : public Atlas
{
private:
	FontAtlas(Texture *texture);

public:
	const AtlasItem* getItem(char id);

protected:
	bool checkProperties(const std::unordered_map<std::string, std::string> &properties) override;
	AtlasItem *createItem(std::unordered_map<std::string, std::string> &propertiesMap) override;
	inline uint16_t getMinItems() override { return 8; }

friend class AtlasManager;
};

} // namespace
