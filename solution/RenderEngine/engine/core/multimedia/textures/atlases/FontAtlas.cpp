#include "FontAtlas.h"

namespace sre
{

FontAtlas::FontAtlas(Texture *texture) : Atlas(texture) {}

bool FontAtlas::checkProperties(const std::unordered_map<std::string, std::string> &properties)
{
	return
	(
		Atlas::checkProperties(properties) &&
		(properties.size() == 5) &&
		(properties.count(keys::ID) > 0) &&
		(properties.count(keys::X) > 0) &&
		(properties.count(keys::Y) > 0) &&
		(properties.count(keys::WIDTH) > 0) &&
		(properties.count(keys::HEIGHT) > 0)
	);
}

AtlasItem FontAtlas::createItem(std::unordered_map<std::string, std::string> &propertiesMap)
{
	AtlasItem baseItem = Atlas::createItem(propertiesMap);
	glm::vec2 offset(this->getValue(propertiesMap, keys::X_OFFSET), this->getValue(propertiesMap, keys::Y_OFFSET));
	float xAdvance = this->getValue(propertiesMap, keys::X_ADVANCE);

	return FontItem(baseItem, offset, xAdvance);
}

} // namespace
