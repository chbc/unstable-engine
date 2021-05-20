#if defined(DEBUG) && !defined(__ANDROID__)

#ifndef _WORLD_EDITOR_H_
#define _WORLD_EDITOR_H_

#include "memory_aliases.h"
#include "IEditorWindow.h"

namespace sre
{
	
class SceneManager;
	
class WorldEditor
{
private:
	SceneManager* sceneManager;
	UPTR<IEditorWindow> menuBar;
	UPTR<IEditorWindow> windows[3];
	bool showDemo;
	
public:
	WorldEditor(SceneManager* arg_sceneManager, bool* editorEnabled);

private:
	void init();
	
	void onEditorGUI();
	void release();

friend class RenderEngine;
};

} // namespace

#endif
#endif
