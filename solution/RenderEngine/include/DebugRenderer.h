#pragma once

#include "ColorMeshData.h"
#include "memory_aliases.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace sre
{

class AGraphicsWrapper;
class ShaderManager;
class CameraComponent;

class DebugRenderer
{
private:
	ShaderManager* shaderManager{ nullptr };
	AGraphicsWrapper* graphicsWrapper{ nullptr };
	uint32_t program;
	std::vector<UPTR<ColorMeshData>> meshes;

private:
	DebugRenderer(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper);

public:
	~DebugRenderer();
	void addBox(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);

private:
	void loadShader();
	void render(CameraComponent* camera);

friend class RenderManager;
};

} // namespace
