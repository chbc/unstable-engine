#ifndef _ATLAS_MANAGER_H_
#define _ATLAS_MANAGER_H_

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

protected:
    void init() override {}
    void release() override;

private:
	Atlas *getAtlas(const std::string &fileName);
	Atlas *loadAtlas(const std::string &baseFileName);
	FontAtlas *getFont(const std::string &fileName);
	FontAtlas *loadFont(const std::string &baseFileName);

friend class GUITextComponent;
friend class GUIImageComponent;
friend class SingletonsManager;
};

} // namespace

#endif
