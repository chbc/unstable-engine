#include "Atlas.h"
#include <fstream>
#include <regex>

namespace sre
{

Atlas::Atlas(Texture *texture)
{
	this->texture = texture;
}

const Rect *Atlas::getItem(char id)
{
	return this->uvs[id].get();
}

void Atlas::loadUVs(const std::string &fontFileName)
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
	const std::string PATTERN("char id=");
	const std::string substr = input.substr(0, PATTERN.length());

	if (std::strcmp(substr.c_str(), PATTERN.c_str()) == 0)
	{
		char *line = const_cast<char *>(input.c_str());

		std::list<std::tuple<std::string, int>> properties;
		this->getProperties(line, properties);
		std::unordered_map<std::string, int> propertiesMap;

		for (std::tuple<std::string, int> item : properties)
		{
			propertiesMap[std::get<0>(item)] = std::get<1>(item);
		}

		this->storeItems(propertiesMap);
	}
}

void Atlas::storeItems(std::unordered_map<std::string, int> &propertiesMap)
{
	char id = propertiesMap["id"];
	float textureWidth = static_cast<float>(this->texture->getWidth());
	float textureHeight = static_cast<float>(this->texture->getHeight());
	glm::vec2 topLeft(static_cast<float>(propertiesMap["x"]) / textureWidth, static_cast<float>(propertiesMap["y"]) / textureHeight);
	glm::vec2 size(static_cast<float>(propertiesMap["width"]) / textureWidth, static_cast<float>(propertiesMap["height"]) / textureHeight);

	UPTR<Rect> uv = std::make_unique<Rect>(topLeft, size);
	this->uvs[id] = std::move(uv);
}

void Atlas::getProperties(const std::string &input, std::list<std::tuple<std::string, int>> &result)
{
	std::regex expression("[a-z]+=\\d+");

	std::sregex_iterator iter(input.begin(), input.end(), expression);
	std::sregex_iterator end;

	std::string propertyInput;
	std::string key;
	int value;
	while (iter != end)
	{
		for (unsigned i = 0; i < iter->size(); ++i)
		{
			propertyInput = (*iter)[i];
			key = this->getKey(propertyInput);
			value = this->getValue(propertyInput);
			result.push_back(std::tuple<std::string, int>(key, value));
		}

		++iter;
	}
}

std::string Atlas::getKey(const std::string &input)
{
	return this->findRegex(input, "\\w+");
}

int Atlas::getValue(const std::string &input)
{
	return std::stoi(this->findRegex(input, "\\d+"));
}

std::string Atlas::findRegex(const std::string &input, const std::string &regex)
{
	std::string result;
	std::regex expression(regex.c_str());
	std::smatch match;

	if (std::regex_search(input, match, expression))
		result = match[0];

	return result;
}

uint32_t Atlas::getTextureId()
{
	return this->texture->getId();
}

} // namespace
