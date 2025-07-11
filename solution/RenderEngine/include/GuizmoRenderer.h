#pragma once

#include "MeshData.h"
#include "memory_aliases.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace sre
{

class AGraphicsWrapper;
class ShaderManager;
class CameraComponent;
class GuizmoComponent;
class AssetsManager;

class GuizmoRenderer
{
private:
	ShaderManager* shaderManager{ nullptr };
	AGraphicsWrapper* graphicsWrapper{ nullptr };
	AssetsManager* assetsManager{ nullptr };
	uint32_t program{ 0 };
	std::list<GuizmoComponent*> guizmoComponents;

private:
	GuizmoRenderer(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper);

public:
	~GuizmoRenderer();

private:
	void addGuizmo(GuizmoComponent* guizmoComponent);
	void loadShader();
	void render(CameraComponent* camera);

	void removeDestroyedEntities();

friend class RenderManager;
};

} // namespace
