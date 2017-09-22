#ifndef _ATLAS_MANAGER_H_
#define _ATLAS_MANAGER_H_

#include <unordered_map>
#include "Atlas.h"
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
	Atlas *getFont(const std::string &fileName);
	Atlas *getAtlas(const std::string &fileName, const std::string &textureExtension, const std::string &configExtension);
	Atlas *loadAtlas(const std::string &textureFile, const std::string &configFile);

friend class GUITextComponent;
friend class GUIImageComponent;
};

} // namespace

#endif
