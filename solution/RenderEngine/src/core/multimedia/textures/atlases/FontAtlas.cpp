#include "FontAtlas.h"
#include "MultimediaManager.h"
#include "SingletonsManager.h"

namespace sre
{

FontAtlas::FontAtlas(Texture *texture) : Atlas(texture) {}

const AtlasItem* FontAtlas::getItem(char id)
{
	return Atlas::getItem(std::to_string(id));
}

bool FontAtlas::checkProperties(const std::unordered_map<std::string, std::string> &properties)
{
	return
	(
		Atlas::checkProperties(properties) &&
		(properties.count(keys::ID) > 0) &&
		(properties.count(keys::X) > 0) &&
		(properties.count(keys::Y) > 0) &&
		(properties.count(keys::WIDTH) > 0) &&
		(properties.count(keys::HEIGHT) > 0)
	);
}

AtlasItem *FontAtlas::createItem(std::unordered_map<std::string, std::string> &propertiesMap)
{
	AtlasItem *baseItem = Atlas::createItem(propertiesMap);
	glm::vec2 offset(this->getValue(propertiesMap, keys::X_OFFSET), this->getValue(propertiesMap, keys::Y_OFFSET));
	float xAdvance = this->getValue(propertiesMap, keys::X_ADVANCE);

	MultimediaManager *multimediaManager = SingletonsManager::getInstance()->get<MultimediaManager>();
	offset = multimediaManager->getNormalizedSize(offset);
	xAdvance = multimediaManager->getNormalizedWidth(xAdvance);

	return new FontItem(baseItem, offset, xAdvance);
}

} // namespace
