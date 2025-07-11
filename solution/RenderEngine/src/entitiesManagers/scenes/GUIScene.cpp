#include "GUIScene.h"
#include "RenderManager.h"

namespace sre
{

// GUITextComponent* GUIScene::frameMSIndicator = nullptr;

GUIScene::GUIScene(std::string arg_name, std::string arg_filePath) : AScene(arg_name, arg_filePath)
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

Entity *GUIScene::createGUIImageEntity(const std::string &filePath, const std::string& name)
{
    Entity *result = this->createEntity(name);
    GUIImageComponent *component = result->addComponent<GUIImageComponent>();
    component->load(filePath);
    return result;
}

Entity* GUIScene::createGUIImageEntity(const std::string& filePath, const glm::vec2& normalizedSize, const std::string& name)
{
    Entity* result = this->createEntity();
    GUIImageComponent* component = result->addComponent<GUIImageComponent>();
    component->load(filePath, normalizedSize);
    return result;
}

Entity *GUIScene::createGUIImageEntityFromAtlas(const std::string &filePath, const std::string &imageId, const std::string& name)
{
    Entity *result = this->createEntity();
    GUIImageComponent *component = result->addComponent<GUIImageComponent>();
    component->loadFromAtlas(filePath, imageId);
    return result;
}

Entity *GUIScene::createGUITextEntity(const std::string fontFile, const std::string& name, uint32_t maxItems)
{
    Entity *result = this->createEntity();
    GUITextComponent *component = result->addComponent<GUITextComponent>();
    component->setMaxItems(maxItems);
    component->load(fontFile);
    component->setText("Text");

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
