#ifndef _GUI_MANAGER_H_
#define _GUI_MANAGER_H_

#include "AScene.h"
#include "GUITextComponent.h"
#include "GUIButtonComponent.h"

namespace sre
{

class GUIScene : public AScene
{
private:
    GUIScene();

private:
	Entity* createGUIImageEntity(uint32_t& index, const std::string& fileName);
	Entity* createGUIImageEntity(uint32_t& index, const std::string& fileName, const glm::vec2& normalizedSize);
	Entity* createGUIImageEntityFromAtlas(uint32_t& index, const std::string& fileName, const std::string& imageId);
	Entity* createGUITextEntity(uint32_t& index, const std::string fontFile, uint32_t maxItems = 100u);

#ifdef DEBUG
    static GUITextComponent *frameMSIndicator;
    static void updateFrameIndicator(int frameTime);
#endif

friend class RenderEngine;
friend class ScenesManager;
};

} // namespace

#endif
