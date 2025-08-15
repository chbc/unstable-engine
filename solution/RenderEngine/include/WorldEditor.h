#if !defined(__ANDROID__)

#pragma once

#include "memory_aliases.h"
#include "IEditorWindow.h"
#include "EditorsController.h"
#include "AEditorPopup.h"

#include <functional>

namespace sre
{
	
class ScenesManager;

using Action = std::function<void(void*)>;
	
class WorldEditor
{
private:
	ScenesManager* scenesManager{ nullptr };
	UPTR<IEditorWindow> menuBar;
	UPTR<IEditorWindow> windows[4];
	UPTR<EditorsController> controller;
	UPTR<AEditorPopup> currentPopup;
	SPTR<Action> showPopupAction;
	bool showDemo{ false };
	bool wasShowingDemo{ false };
	
public:
	WorldEditor(ScenesManager* arg_scenesManager);

private:
	void init();
	void onUpdate(float elapsedTime);
	bool onEditorGUI();
	void onGUIEnd();
	void onShowPopup(void* message);
	void cleanUp();
	void release();

friend class EditorStrategy;
};

} // namespace

#endif
