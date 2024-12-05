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

class EditorSceneTree : public IEditorWindow
{
private:
	ScenesManager* scenesManager;
	Entity* selectedEntity;
	SPTR<Action> selectionAction;

public:
	EditorSceneTree(ScenesManager* arg_scenesManager);
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
