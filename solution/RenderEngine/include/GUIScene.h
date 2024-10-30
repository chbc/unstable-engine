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
	Entity* createGUIImageEntity(const std::string& fileName, const std::string& name = "");
	Entity* createGUIImageEntity(const std::string& fileName, const glm::vec2& normalizedSize, const std::string& name = "");
	Entity* createGUIImageEntityFromAtlas(const std::string& fileName, const std::string& imageId, const std::string& name = "");
	Entity* createGUITextEntity(const std::string fontFile, uint32_t maxItems = 100u, const std::string& name = "");

#ifdef DEBUG
	// MOVER PARA ScenesManager
    // XXX static GUITextComponent *frameMSIndicator;
    static void updateFrameIndicator(int frameTime);
#endif

friend class AExecutionStrategy;
friend class ScenesManager;
};

} // namespace

#endif
