#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"

namespace sre
{

class ScenesManager;

class EditorSceneTree : public IEditorWindow
{
private:
	ScenesManager* scenesManager;
	class Entity* selectedEntity;

public:
	EditorSceneTree(ScenesManager* arg_scenesManager);
	void onInit() override;
	void onEditorGUI() override;

private:
	void drawScene(class AScene* scene);
	void drawEntityTree(class Entity* entity, int index);
};

} // namespace

#endif
