#if defined(DEBUG) && !defined(__ANDROID__)
#pragma once

#include "IEditorWindow.h"
#include "FileIcon.h"
#include "memory_aliases.h"
#include "ImportMeshPopup.h"

#include <vector>
#include <functional>

namespace sre
{

class EditorsController;

using Action = std::function<void(void*)>;

class EditorFileBrowser : public IEditorWindow
{

private:
	std::vector<UPTR<FileIcon>> fileIcons;
	SPTR<Action> externalFileDropAction;
	SPTR<Action_OnClosePopup> onClosePopupAction;
	EditorsController* controller{ nullptr };
	std::string gameContentFolder;
	std::string engineContentFolder;
	std::string currentDirectory;
	FileIcon* selectedItem{ nullptr };

public:
	EditorFileBrowser(EditorsController* arg_controller);
	void onInit() override;
	void onEditorGUI() override;
	void onCleanUp() override;

private:
	void handleExternalFileDrop(void* message);
};

} // namespace

#endif
