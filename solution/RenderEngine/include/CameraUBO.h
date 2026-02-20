#pragma once

#include <glm/mat4x4.hpp>

namespace sre
{

struct CameraUBO
{
	glm::mat4 projectionMatrix{ 1.0f };
	glm::mat4 viewMatrix{ 1.0f };
	// glm::vec4 cameraPosition{ 0.0f };
};

} // namespace
