#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"

namespace sre
{

class EditorEntityProperties : public IEditorWindow
{
private:
	class Entity* entity;

public:
	EditorEntityProperties();
	void onEditorGUI() override;

private:
	void onEntitySelected(void* data);
};

} // namespace

#endif
