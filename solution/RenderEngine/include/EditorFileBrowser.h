#if defined(DEBUG) && !defined(__ANDROID__)
#pragma once

#include "IEditorWindow.h"
#include "FileIcon.h"
#include "memory_aliases.h"

#include <vector>

namespace sre
{

class EditorsController;

class EditorFileBrowser : public IEditorWindow
{

private:
	std::vector<UPTR<FileIcon>> fileIcons;
	EditorsController* controller;

public:
	EditorFileBrowser(EditorsController* arg_controller);
	void onInit() override;
	void onEditorGUI() override;
};

} // namespace

#endif
