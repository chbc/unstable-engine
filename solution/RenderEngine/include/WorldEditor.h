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
	UPTR<IEditorWindow> windows[3];
	bool showDemo;
	
private:
	void init(SceneManager* sceneManager, bool* editorEnabled);
	void XXX_MessageMethod(void* message);
	
	void onEditorGUI();

friend class RenderEngine;
};

} // namespace

#endif
#endif
