#pragma once

#include "memory_aliases.h"
#include "EditorMessages.h"

#include <glm/mat4x4.hpp>

namespace ImGuizmo
{
	enum OPERATION : int;
}

namespace sre
{

class Entity;

class SceneViewportGuizmos
{
private:
	Entity* selectedEntity{ nullptr };
	Entity* guizmoEntity{ nullptr };
	SPTR<Action> selectionAction;
	ImGuizmo::OPERATION guizmoOperation{ 0u };

public:
	SceneViewportGuizmos();
	void onInit();
	bool drawAndManipulate(float windowWidth, float windowHeight, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void processGuizmoOperationSelection();
	void onCleanUp();

private:
	void onEntitySelected(void* data);
};

} // namespace
