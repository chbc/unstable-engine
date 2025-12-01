#pragma once

#include "AEntityComponent.h"
#include <glm/vec3.hpp>
#include "ShadowData.h"
#include "memory_aliases.h"

namespace sre
{

class SRE_API ALightComponent : public AEntityComponent
{
private:
    glm::vec3 color{ 0.0f, 0.0f, 0.0f };
    UPTR<ShadowData> shadowData;

protected:
	ALightComponent(Entity *entity);
    class LightManager* lightManager{ nullptr };
	size_t propertyChangedCallbackId{ 0 };

public:
    void setColor(const glm::vec3 &color);
    glm::vec3 getColor();

private:
    inline bool hasShadowData() { return (this->shadowData.get() != nullptr); }
	void setupShadowData(uint32_t fbo, uint32_t textureId, uint32_t textureUnit);

friend class LightManager;
friend class ShadowRenderer;
friend class ShadowRendererShaderSetup;
};

} // namespace
