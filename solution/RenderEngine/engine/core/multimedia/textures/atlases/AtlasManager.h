#ifndef _ATLAS_MANAGER_H_
#define _ATLAS_MANAGER_H_

#include <unordered_map>
#include "FontAtlas.h"
#include <engine/utils/singleton_macros.h>

namespace sre
{

class AtlasManager
{
DECLARE_SINGLETON(AtlasManager)

private:
	// <path, atlas>
	std::unordered_map<std::string, UPTR<Atlas>> atlases;

private:
	Atlas *getAtlas(const std::string &fileName);
	Atlas *loadAtlas(const std::string &baseFileName);
	FontAtlas *getFont(const std::string &fileName);
	FontAtlas *loadFont(const std::string &baseFileName);

friend class GUITextComponent;
friend class GUIImageComponent;
};

} // namespace

#endif
