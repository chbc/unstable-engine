#ifndef _ALIGHT_COMPONENT_H_
#define _ALIGHT_COMPONENT_H_

#include "AEntityComponent.h"
#include <glm/vec3.hpp>
#include "ShadowData.h"
#include "memory_aliases.h"

namespace sre
{

/*!
    Base class to handle lighting.
*/
class ALightComponent : public AEntityComponent
{
private:
    glm::vec3 color;
    UPTR<ShadowData> shadowData;

protected:
	ALightComponent(Entity *entity);

public:
    void setColor(const glm::vec3 &color);
    glm::vec3 getColor();

private:
    inline bool hasShadowData() { return (this->shadowData.get() != nullptr); }

friend class LightManager;
friend class ShadowRenderer;
friend class ShadowRendererShaderSetup;
};

} // namespace

#endif
