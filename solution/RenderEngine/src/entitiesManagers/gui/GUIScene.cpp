#include "GUIScene.h"

namespace sre
{

GUITextComponent* GUIScene::frameMSIndicator = nullptr;

GUIScene::GUIScene() : AScene("guiScene")
{
	/* ###
#ifdef DEBUG
    Entity *entity = createGUITextEntity("../../media/fonts/verdana", 6);
    this->frameMSIndicator = entity->getComponent<GUITextComponent>();
    this->frameMSIndicator->setUIPosition(glm::vec2(0.025f, 0.025f));
    entity->getTransform()->setScale(glm::vec3(0.5f, 0.5f, 1.0f));
    this->addEntity(entity, "_frame_indicator");
#endif
*/
}

Entity *GUIScene::createGUIImageEntity(uint32_t& index, const std::string &fileName)
{
    Entity *result = this->createEntity(index);
    GUIImageComponent *component = result->addComponent<GUIImageComponent>();
    component->load(fileName);
    return result;
}

Entity* GUIScene::createGUIImageEntity(uint32_t& index, const std::string& fileName, const glm::vec2& normalizedSize)
{
    Entity* result = this->createEntity(index);
    GUIImageComponent* component = result->addComponent<GUIImageComponent>();
    component->load(fileName, normalizedSize);
    return result;
}

Entity *GUIScene::createGUIImageEntityFromAtlas(uint32_t& index, const std::string &fileName, const std::string &imageId)
{
    Entity *result = this->createEntity(index);
    GUIImageComponent *component = result->addComponent<GUIImageComponent>();
    component->loadFromAtlas(fileName, imageId);
    return result;
}

Entity *GUIScene::createGUITextEntity(uint32_t& index, const std::string fontFile, uint32_t maxItems)
{
    Entity *result = this->createEntity(index);
    GUITextComponent *component = result->addComponent<GUITextComponent>(maxItems);
    component->loadFont(fontFile);

    return result;
}

#ifdef DEBUG
void GUIScene::updateFrameIndicator(int frameTime)
{
    frameMSIndicator->setText(std::to_string(frameTime));
}
#endif

} // namespace
