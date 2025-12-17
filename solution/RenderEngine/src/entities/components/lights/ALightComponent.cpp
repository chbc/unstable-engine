#include "ALightComponent.h"
#include "Entity.h"
#include "ColorEditorProperty.h"
#include "SingletonsManager.h"
#include "TextureCreator.h"
#include "AGraphicsWrapper.h"

namespace sre
{

ALightComponent::ALightComponent(Entity *entity, bool useCubemap)
    : AEntityComponent(entity), color(glm::vec3(0.6f, 0.6f, 0.6f)),
    shadowData(UPTR<ShadowData>{nullptr})
{
    this->addEditorProperty(new ColorEditorProperty{ "Color", this->color });
}

ALightComponent::~ALightComponent()
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    TextureCreator* textureCreator = singletonsManager->get<TextureCreator>();
    textureCreator->deleteTexture(this->shadowData->textureId);
}

void ALightComponent::setColor(const glm::vec3 &color)
{
    this->color = color;
}

glm::vec3 ALightComponent::getColor()
{
    return this->color;
}

void ALightComponent::updateShadowTextureUnit(uint32_t unit)
{
	this->shadowData->textureUnit = unit;
}

} // namespace
