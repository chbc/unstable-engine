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

public:
	EditorSceneTree(SceneManager* arg_sceneManager);
	void onEditorGUI() override;

private:
	void drawEntityTree(class Entity* entity, int index) const;
};

} // namespace

#endif
