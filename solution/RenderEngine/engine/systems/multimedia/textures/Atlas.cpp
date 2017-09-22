#include "Atlas.h"
#include <fstream>
#include <regex>

namespace sre
{

Atlas::Atlas(Texture *texture)
{
	this->texture = texture;
}

const Rect &Atlas::getItem(const std::string &id)
{
	return this->uvs[id];
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

		std::list<std::tuple<std::string, std::string>> properties;
		this->getProperties(line, properties);
		std::unordered_map<std::string, std::string> propertiesMap;

		for (std::tuple<std::string, std::string> item : properties)
		{
			propertiesMap[std::get<0>(item)] = std::get<1>(item);
		}

		this->storeItems(propertiesMap);
	}
}

void Atlas::storeItems(std::unordered_map<std::string, std::string> &propertiesMap)
{
	std::string id = propertiesMap["id"];
	float textureWidth = static_cast<float>(this->texture->getWidth());
	float textureHeight = static_cast<float>(this->texture->getHeight());
	glm::vec2 topLeft(std::stof(propertiesMap["x"].c_str()) / textureWidth, std::stof(propertiesMap["y"].c_str()) / textureHeight);
	glm::vec2 size(std::stof(propertiesMap["width"].c_str()) / textureWidth, std::stof(propertiesMap["height"].c_str()) / textureHeight);

	this->uvs[id] = Rect(topLeft, size);
}

void Atlas::getProperties(const std::string &input, std::list<std::tuple<std::string, std::string>> &result)
{
	std::regex expression("[a-z]+=\\d+");

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
			key = this->findRegex(propertyInput, "\\w+");
			value = this->findRegex(propertyInput, "\\d+");
			result.push_back(std::tuple<std::string, std::string>(key, value));
		}

		++iter;
	}
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
