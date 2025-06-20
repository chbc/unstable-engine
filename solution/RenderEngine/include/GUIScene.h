#pragma once

#include "AScene.h"
#include "GUIImageComponent.h"
#include "GUITextComponent.h"
#include "GUIButtonComponent.h"

namespace sre
{

class GUIScene : public AScene
{
private:
    GUIScene(std::string name, std::string arg_filePath);

private:
	Entity* createGUIImageEntity(const std::string& filePath, const std::string& name);
	Entity* createGUIImageEntity(const std::string& filePath, const glm::vec2& normalizedSize, const std::string& name);
	Entity* createGUIImageEntityFromAtlas(const std::string& filePath, const std::string& imageId, const std::string& name);
	Entity* createGUITextEntity(const std::string fontFile, const std::string& name, uint32_t maxItems);

#ifdef DEBUG
	// MOVER PARA ScenesManager
    // XXX static GUITextComponent *frameMSIndicator;
    static void updateFrameIndicator(int frameTime);
#endif

friend class AExecutionStrategy;
friend class ScenesManager;
};

} // namespace
