#if !defined(RELEASE) && !defined(__ANDROID__)

#ifndef _WORLD_EDITOR_H_
#define _WORLD_EDITOR_H_

#include "memory_aliases.h"
#include "IEditorWindow.h"
#include "EditorsController.h"

namespace sre
{
	
class ScenesManager;
	
class WorldEditor
{
private:
	ScenesManager* scenesManager;
	UPTR<IEditorWindow> menuBar;
	UPTR<IEditorWindow> windows[3];
	UPTR<EditorsController> controller;
	bool showDemo;
	bool wasShowingDemo;
	
public:
	WorldEditor(ScenesManager* arg_scenesManager);

private:
	void init();
	void onUpdate(float elapsedTime);
	void onEditorGUI();
	void release();

friend class EditorStrategy;
};

} // namespace

#endif
#endif
