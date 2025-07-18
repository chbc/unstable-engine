#pragma once

#include <unordered_map>
#include "FontAtlas.h"
#include "ASingleton.h"

namespace sre
{

class AtlasManager : public ASingleton
{

private:
	// <path, atlas>
	std::unordered_map<std::string, UPTR<Atlas>> atlases;

public:
	FontAtlas* getFont(const std::string &filePath);

protected:
    void release() override;

private:
	Atlas* getAtlas(const std::string &filePath);
	Atlas* loadAtlas(const std::string &baseFileName);
	FontAtlas* loadFont(const std::string &baseFileName);
	Texture* loadTexture(const std::string& baseFileName);

friend class GUITextComponent;
friend class GUIImageComponent;
friend class SingletonsManager;
};

} // namespace
