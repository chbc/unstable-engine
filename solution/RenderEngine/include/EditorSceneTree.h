#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"

namespace sre
{

class SceneManager;

class EditorSceneTree : public IEditorWindow
{
private:
	SceneManager* sceneManager;
	class Entity* selectedEntity;

public:
	EditorSceneTree(SceneManager* arg_sceneManager);
	void onInit() override;
	void onEditorGUI() override;

private:
	void drawEntityTree(class Entity* entity, int index);
};

} // namespace

#endif
