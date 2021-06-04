#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"

namespace sre
{

class EditorMenuBar : public IEditorWindow
{
private:
	bool* isDemoEnabled;

public:
	EditorMenuBar(bool* demoEnabled);

	void onEditorGUI() override;

private:
	void exitEditor();
};

} // namespace

#endif
