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
	Atlas *loadAtlas(const std::string &fileName);

friend class GUITextComponent;
};

} // namespace

#endif
