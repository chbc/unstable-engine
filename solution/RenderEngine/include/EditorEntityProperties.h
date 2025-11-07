#if !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"
#include "AEntityComponent.h"
#include <glm/vec3.hpp>
#include <vector>
#include <unordered_map>

namespace sre
{

class EditorsController;

using Action = std::function<void(void*)>;

class EditorEntityProperties : public IEditorWindow
{
private:
	EditorsController* controller{ nullptr };
	bool addingComponent{ false };
	int currentAddedComponent{ 0 };

public:
	EditorEntityProperties(EditorsController* arg_controller);
	void onEditorGUI() override;

private:
	void drawAddComponentButton(Entity* selectedEntity);
};

} // namespace

#endif
