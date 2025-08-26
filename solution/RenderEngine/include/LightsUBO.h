#pragma once

#include <glm/vec4.hpp>

namespace sre
{

struct LightsUBO
{
    struct DirectionalLight
    {
        glm::vec4 direction{ 0.0f };
        glm::vec4 color{ 1.0f };
    };

    struct PointLight
    {
        glm::vec4 position{ 0.0f };
        glm::vec4 color{ 1.0f };
        glm::vec4 rangeAndIntensity{ 0.0f };
    };

    DirectionalLight directionalLights[4];
    PointLight pointLights[4];

    int maxDirectionalLights;
    int maxPointLights;
};

} // namespace sre
