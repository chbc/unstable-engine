#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"

namespace sre
{

class EditorsController;

class EditorMenuBar : public IEditorWindow
{
private:
	bool* isDemoEnabled;
	EditorsController* controller;

public:
	EditorMenuBar(bool* demoEnabled, EditorsController* arg_controller);

	void onEditorGUI() override;

private:
	void drawFileGroup();
	void drawEditGroup();
	void drawEntitiesGroup();
	void drawHelpGroup();
	void exitEditor();
};

} // namespace

#endif
