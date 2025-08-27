#pragma once

#include "ALightComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace sre
{

class SRE_API DirectionalLightComponent : public ALightComponent
{
DECLARE_COMPONENT()

private:
	glm::mat4 lightSpaceMatrix{ 1.0f };

public:
	DirectionalLightComponent(Entity *entity);

protected:
	void onPropertyChanged() override;

friend class Entity;
friend class ShadowRenderer;
friend class ShadowRendererShaderSetup;
};

} // namespace
