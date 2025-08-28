#pragma once

#include "EditorMessages.h"
#include "memory_aliases.h"

#include <glm/mat4x4.hpp>

namespace ImGuizmo
{
	enum OPERATION : int;
	enum MODE : int;
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
	SPTR<Action> orientationModeAction;
	SPTR<Action> gridEnabledAction;
	ImGuizmo::OPERATION guizmoOperation{ 0u };
	ImGuizmo::MODE guizmoMode{ 0u };
	bool gridEnabled{ true };

public:
	SceneViewportGuizmos();
	void onInit();
	bool drawAndManipulate(bool cameraMoving, const glm::vec2& windowPos, const glm::vec2& windowSize, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void processGuizmoOperationSelection();
	void onCleanUp();

private:
	void onEntitySelected(void* data);
	void onEntityManipulated();
	void onOrientationModeChanged(void* message);
	void onSetGridEnabled(void* message);
};

} // namespace
