#include "Atlas.h"
#include <fstream>
#include <regex>
#include <engine/core/multimedia/MultimediaManager.h>

namespace sre
{

Atlas::Atlas(Texture *texture)
{
	this->texture = texture;
}

bool Atlas::checkProperties(const std::unordered_map<std::string, std::string> &properties)
{
	return
	(
		(properties.size() >= this->getMinItems()) &&
		(properties.count(keys::ID) > 0) &&
		(properties.count(keys::X) > 0) &&
		(properties.count(keys::Y) > 0) &&
		(properties.count(keys::WIDTH) > 0) &&
		(properties.count(keys::HEIGHT) > 0)
	);
}

AtlasItem *Atlas::createItem(std::unordered_map<std::string, std::string> &propertiesMap)
{
	float textureWidth = static_cast<float>(this->texture->getWidth());
	float textureHeight = static_cast<float>(this->texture->getHeight());

	glm::vec2 positions(getValue(propertiesMap, keys::X), getValue(propertiesMap, keys::Y));
	glm::vec2 pixelSize(getValue(propertiesMap, keys::WIDTH), getValue(propertiesMap, keys::HEIGHT));

	glm::vec2 uvPositions(positions.x / textureWidth, positions.y / textureHeight);
	glm::vec2 uvSize(pixelSize.x / textureWidth, pixelSize.y / textureHeight);
	glm::vec2 screenBasedSize = MultimediaManager::getInstance()->getNormalizedSize(pixelSize);

	return new AtlasItem(Rect(uvPositions, uvSize), pixelSize, screenBasedSize);
}

uint16_t Atlas::getMinItems()
{
	return 5;
}

float Atlas::getValue(std::unordered_map<std::string, std::string> &propertiesMap, const std::string &key)
{
	return std::stof(propertiesMap[key].c_str());
}

const AtlasItem *Atlas::getItem(const std::string &id)
{
	return this->items[id].get();
}

void Atlas::load(const std::string &fontFileName)
{
	std::string line;
	std::ifstream file(fontFileName);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			this->processLine(line);
		}
		file.close();
	}
	else
		throw "Couldn't find file: " + fontFileName;
}

void Atlas::processLine(const std::string &input)
{
	if (input.find("id=") != std::string::npos)
	{
		std::unordered_map<std::string, std::string> propertiesMap;
		this->getProperties(input, propertiesMap);

		if (this->checkProperties(propertiesMap))
		{
			std::string id = propertiesMap[keys::ID];
			this->items[id] = UPTR<AtlasItem>{ this->createItem(propertiesMap) };
		}
	}
}

void Atlas::getProperties(const std::string &input, std::unordered_map<std::string, std::string> &result)
{
	std::regex expression("\\w+=-?\\w+");

	std::sregex_iterator iter(input.begin(), input.end(), expression);
	std::sregex_iterator end;

	std::string propertyInput;
	std::string key;
	std::string value;
	while (iter != end)
	{
		for (unsigned i = 0; i < iter->size(); ++i)
		{
			propertyInput = (*iter)[i];
			size_t equalsPosition = propertyInput.find('=');
			key = propertyInput.substr(0, equalsPosition);
			value = propertyInput.substr(equalsPosition + 1);
			result[key] = value;
		}

		++iter;
	}
}

uint32_t Atlas::getTextureId()
{
	return this->texture->getId();
}

} // namespace
