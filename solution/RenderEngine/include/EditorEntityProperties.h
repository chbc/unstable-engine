#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"
#include "AEntityComponent.h"
#include <glm/vec3.hpp>
#include <vector>
#include <unordered_map>

namespace sre
{

using Action = std::function<void(void*)>;

class EditorEntityProperties : public IEditorWindow
{
private:
	class Entity* entity;
	SPTR<Action> selectionAction;

public:
	EditorEntityProperties();
	void onInit() override;
	void onEditorGUI() override;
	void onCleanUp() override;
	void onRelease() override;

private:
	void onEntitySelected(void* data);
};

} // namespace

#endif
