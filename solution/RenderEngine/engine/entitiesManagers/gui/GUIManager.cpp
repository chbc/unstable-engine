#include "GUIManager.h"

#include <sstream>

namespace sre
{

GUIManager::GUIManager() : AEntityManager() 
{
#ifdef DEBUG
    Entity *entity = createGUITextEntity("../../media/fonts/verdana", 6);
    this->frameMSIndicator = entity->getComponent<GUITextComponent>();
    this->frameMSIndicator->setUIPosition(glm::vec2(0.025f, 0.025f));
    entity->getTransform()->setScale(glm::vec3(0.5f, 0.5f, 1.0f));
    this->addEntity(entity, "_frame_indicator");
#endif
}

Entity *GUIManager::createGUIImageEntity(const std::string &fileName)
{
    Entity *result = this->createEntity();
    GUIImageComponent *component = result->addComponent<GUIImageComponent>();
    component->load(fileName);
    return result;
}

Entity *GUIManager::createGUIImageEntityFromAtlas(const std::string &fileName, const std::string &imageId)
{
    Entity *result = this->createEntity();
    GUIImageComponent *component = result->addComponent<GUIImageComponent>();
    component->loadFromAtlas(fileName, imageId);
    return result;
}

Entity *GUIManager::createGUITextEntity(const std::string fontFile, uint32_t maxItems)
{
    Entity *result = this->createEntity();
    GUITextComponent *component = result->addComponent<GUITextComponent>(maxItems);
    component->loadFont(fontFile);

    return result;
}

#ifdef DEBUG
std::stringstream frameIndicatorStream;

void GUIManager::updateFrameIndicator(int frameTime)
{
    frameIndicatorStream << frameTime;
    this->frameMSIndicator->setText(frameIndicatorStream.str());
    frameIndicatorStream.str(std::string());
    frameIndicatorStream.clear();
}
#endif

} // namespace
