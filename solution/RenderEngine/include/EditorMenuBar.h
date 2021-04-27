#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"

namespace sre
{

class EditorMenuBar : public IEditorWindow
{
private:
	bool* isEditorEnabled;
	bool* isDemoEnabled;

public:
	EditorMenuBar(bool* editorEnabled, bool* demoEnabled);

	void onEditorGUI() override;
};

} // namespace

#endif
