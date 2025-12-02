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

    this->setupShadowData(useCubemap);
}

void ALightComponent::setColor(const glm::vec3 &color)
{
    this->color = color;
}

glm::vec3 ALightComponent::getColor()
{
    return this->color;
}

void ALightComponent::setupShadowData(bool useCubemap)
{
    SingletonsManager* singletonsManager = SingletonsManager::getInstance();
    TextureCreator* textureCreator = singletonsManager->get<TextureCreator>();
	AGraphicsWrapper* graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();

    Texture* texture{ nullptr };
    if (useCubemap)
    {
        texture = textureCreator->createShadowCubemapTexture(1024, 1024);
    }
    else
    {
        texture = textureCreator->createShadowTexture(1024, 1024);
    }
    
    uint32_t fbo = graphicsWrapper->generateDepthFrameBuffer(texture->getId(), useCubemap);
	this->shadowData = UPTR<ShadowData>(new ShadowData{ fbo, texture->getId(), texture->getUnit() });
}

} // namespace
