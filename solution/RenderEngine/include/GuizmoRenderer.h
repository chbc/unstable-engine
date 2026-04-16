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
class AColliderComponent;

class GuizmoRenderer
{
private:
	ShaderManager* shaderManager{ nullptr };
	AGraphicsWrapper* graphicsWrapper{ nullptr };
	AssetsManager* assetsManager{ nullptr };
	uint32_t program{ 0 };
	std::list<GuizmoComponent*> meshGuizmos;
	std::list<GuizmoComponent*> boxColliderGuizmos;
	std::list<GuizmoComponent*> sphereColliderGuizmos;

private:
	GuizmoRenderer(ShaderManager* shaderManager, AGraphicsWrapper* graphicsWrapper);

public:
	~GuizmoRenderer();

private:
	void addGuizmos(Entity* entity);
	void loadShader();
	void render();
	void renderMeshGuizmo(GuizmoComponent* guizmoComponent);
	// void renderColliderGuizmo(GuizmoComponent* guizmoComponent, AColliderComponent* collider);
	void removeGuizmos(Entity* entity);

friend class RenderManager;
};

} // namespace
