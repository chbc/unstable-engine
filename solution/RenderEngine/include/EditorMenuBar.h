#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"

namespace sre
{

class ScenesManager;

class EditorMenuBar : public IEditorWindow
{
private:
	bool* isDemoEnabled;
	ScenesManager* scenesManager;

public:
	EditorMenuBar(bool* demoEnabled, ScenesManager* arg_scenesManager);

	void onEditorGUI() override;

private:
	void exitEditor();
};

} // namespace

#endif
