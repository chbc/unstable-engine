#include "GUIScene.h"
#include "RenderManager.h"

namespace sre
{

// GUITextComponent* GUIScene::frameMSIndicator = nullptr;

GUIScene::GUIScene() : AScene("guiScene")
{
/*
#ifdef DEBUG
    Entity *entity = createGUITextEntity("fonts/verdana", 6, "_frame_indicator");
    this->frameMSIndicator = entity->getComponent<GUITextComponent>();
    this->frameMSIndicator->setUIPosition(glm::vec2(0.025f, 0.025f));
    entity->getTransform()->setScale(glm::vec3(0.5f, 0.5f, 1.0f));
#endif
*/
}

Entity *GUIScene::createGUIImageEntity(const std::string &fileName, const std::string& name)
{
    Entity *result = this->createEntity(name);
    GUIImageComponent *component = result->addComponent<GUIImageComponent>();
    component->load(fileName);
    this->renderManager->addEntity(result);
    return result;
}

Entity* GUIScene::createGUIImageEntity(const std::string& fileName, const glm::vec2& normalizedSize, const std::string& name)
{
    Entity* result = this->createEntity();
    GUIImageComponent* component = result->addComponent<GUIImageComponent>();
    component->load(fileName, normalizedSize);
    return result;
}

Entity *GUIScene::createGUIImageEntityFromAtlas(const std::string &fileName, const std::string &imageId, const std::string& name)
{
    Entity *result = this->createEntity();
    GUIImageComponent *component = result->addComponent<GUIImageComponent>();
    component->loadFromAtlas(fileName, imageId);
    return result;
}

Entity *GUIScene::createGUITextEntity(const std::string fontFile, const std::string& name, uint32_t maxItems)
{
    Entity *result = this->createEntity();
    GUITextComponent *component = result->addComponent<GUITextComponent>();
    component->setMaxItems(maxItems);
    component->loadFont(fontFile);

    return result;
}

#ifdef DEBUG
void GUIScene::updateFrameIndicator(int frameTime)
{
    /*
    frameMSIndicator->setText(std::to_string(frameTime));
    */
}
#endif

} // namespace
