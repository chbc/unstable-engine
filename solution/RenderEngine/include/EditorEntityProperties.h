#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"

namespace sre
{

class EditorEntityProperties : public IEditorWindow
{
public:
	void onEditorGUI() override;
};

} // namespace

#endif
