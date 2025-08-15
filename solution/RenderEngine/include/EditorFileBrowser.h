#if !defined(__ANDROID__)
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
	SPTR<Action> entitySelectionAction;
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
	void setupColumns(const ImVec2& iconSize);
	void showRootContentButtons();
	void showIcon(FileIcon* icon, const ImVec2& size);
	void handleDelete();
	void handleIconDrag(FileIcon* icon, const ImVec2& size);
	void handleExternalFileDrop(void* message);
	void onEntitySelected(void* data);
};

} // namespace

#endif
