#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"
#include "memory_aliases.h"
#include <functional>

namespace sre
{

class ScenesManager;
class Entity;
using Action = std::function<void(void*)>;
class EditorsController;

class EditorSceneTree : public IEditorWindow
{
private:
	ScenesManager* scenesManager{ nullptr };
	Entity* selectedEntity{ nullptr };
	SPTR<Action> selectionAction;
	EditorsController* controller{ nullptr };

public:
	EditorSceneTree(ScenesManager* arg_scenesManager, EditorsController* arg_controller);
	void onInit() override;
	void onEditorGUI() override;
	void onCleanUp() override;

private:
	void drawScene(class AScene* scene);
	void drawEntityTree(Entity* entity, int index);
	void notifySelection(Entity* entity);
	void onEntitySelected(void* data);
};

} // namespace

#endif
