#ifndef _GUI_MANAGER_H_
#define _GUI_MANAGER_H_

#include "../AEntityManager.h"
#include <engine/entities/components/renderables/gui/GUITextComponent.h>

namespace sre
{

class GUIManager : public AEntityManager
{
public:
    Entity *createGUIImageEntity(const std::string &fileName);
    Entity *createGUIImageEntityFromAtlas(const std::string &fileName, const std::string &imageId);
    Entity *createGUITextEntity(const std::string fontFile);

private:
    GUITextComponent *frameMSIndicator;

private:
    GUIManager();

friend class RenderEngine;
};

} // namespace

#endif
