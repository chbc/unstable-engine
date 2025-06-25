#pragma once

#include "Rect.h"
#include "memory_aliases.h"
#include "Texture.h"

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
	glm::vec2 pixelSize{ 0.0f, 0.0f };
	glm::vec2 normalizedSize{ 0.0f, 0.0f };

	AtlasItem(Rect uv, glm::vec2 pixelSize, glm::vec2 normalizedSize)
		: uv(uv), pixelSize(pixelSize), normalizedSize(normalizedSize) { }
};

class Atlas
{
private:
	Texture* texture;

	// <id, item>
	std::unordered_map<std::string, UPTR<AtlasItem>> items;

public:
	const AtlasItem *getItem(const std::string &id);
	Texture* getTexture();
	std::string getFilePath();

protected:
	Atlas(Texture *texture);

	virtual bool checkProperties(const std::unordered_map<std::string, std::string> &properties);
	virtual AtlasItem *createItem(std::unordered_map<std::string, std::string> &propertiesMap);
	virtual uint16_t getMinItems();
	float getValue(std::unordered_map<std::string, std::string> &propertiesMap, const std::string &key);

private:
	void load(const std::string& filePath);
	void processLine(const std::string &input);
	void getProperties(const std::string &input, std::unordered_map<std::string, std::string> &result);


friend class AtlasManager;
friend class GUITextComponent;
friend class GUIImageComponent;
};

} // namespace
