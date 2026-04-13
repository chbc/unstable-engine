#pragma once

#include "MeshData.h"
#include "memory_aliases.h"

#include <unordered_map>
#include <glm/mat4x4.hpp>

namespace sre
{

class AGraphicsWrapper;
class ShaderManager;
class AssetsManager;
class GuizmoComponent;
class Entity;
class BoxColliderComponent;

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
	void render();
	void renderMeshGuizmo(GuizmoComponent* guizmoComponent);
	void renderColliderGuizmo(GuizmoComponent* guizmoComponent, BoxColliderComponent* collider);
	void removeGuizmo(GuizmoComponent* guizmoComponent);

friend class RenderManager;
};

} // namespace
