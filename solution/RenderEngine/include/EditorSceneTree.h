#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"
#include "memory_aliases.h"
#include <functional>

namespace sre
{

class ScenesManager;
class AScene;
class Entity;
using Action = std::function<void(void*)>;
class EditorsController;

class EditorSceneTree : public IEditorWindow
{
private:
	AScene* scene{ nullptr };
	AScene* guiScene{ nullptr };
	EditorsController* controller{ nullptr };

public:
	EditorSceneTree(EditorsController* arg_controller);
	void onInit() override;
	void onEditorGUI() override;

private:
	void drawScene(class AScene* scene);
	void drawEntityTree(Entity* entity, int index);
};

} // namespace

#endif
