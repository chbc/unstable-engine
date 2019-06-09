#ifndef _GUI_MANAGER_H_
#define _GUI_MANAGER_H_

#include "AEntityManager.h"
#include "GUITextComponent.h"

namespace sre
{

class GUIManager : public AEntityManager
{
public:
    Entity *createGUIImageEntity(const std::string &fileName);
    Entity *createGUIImageEntityFromAtlas(const std::string &fileName, const std::string &imageId);
    Entity *createGUITextEntity(const std::string fontFile, uint32_t maxItems = 100u);

private:
    GUIManager();

#ifdef DEBUG
    GUITextComponent *frameMSIndicator;
    void updateFrameIndicator(int frameTime);
#endif

friend class RenderEngine;
};

} // namespace

#endif
