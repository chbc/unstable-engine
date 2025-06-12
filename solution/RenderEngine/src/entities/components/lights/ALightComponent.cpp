#include "ALightComponent.h"
#include "Entity.h"
#include "ColorEditorProperty.h"

namespace sre
{

ALightComponent::ALightComponent(Entity *entity) 
    : AEntityComponent(entity), color(glm::vec3(0.6f, 0.6f, 0.6f)),
    shadowData(UPTR<ShadowData>{nullptr})
{
    this->addEditorProperty(new ColorEditorProperty{ "Color", this->color });
}

void ALightComponent::setColor(const glm::vec3 &color)
{
    this->color = color;
}

glm::vec3 ALightComponent::getColor()
{
    return this->color;
}

} // namespace
