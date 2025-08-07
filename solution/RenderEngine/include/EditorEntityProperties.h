#if defined(DEBUG) && !defined(__ANDROID__)

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

public:
	EditorEntityProperties(EditorsController* arg_controller);
	void onEditorGUI() override;
};

} // namespace

#endif
