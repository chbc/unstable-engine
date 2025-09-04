#if !defined(__ANDROID__)
#pragma once

#include "IEditorWindow.h"
#include "FileIcon.h"
#include "memory_aliases.h"
#include "ExternalFileDropHandler.h"

#include <vector>
#include <functional>

namespace sre
{

class EditorsController;

class EditorFileBrowser : public IEditorWindow
{
private:
	ExternalFileDropHandler externalFileDropHandler;
	std::vector<UPTR<FileIcon>> fileIcons;
	SPTR<Action> entitySelectionAction;
	SPTR<Action> refreshIconsAction;
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
	void refreshFileIcons();
	std::string getCurrentDirectory() const;

private:
	void setupColumns(const ImVec2& iconSize);
	void showRootContentButtons();
	void showIcon(FileIcon* icon, const ImVec2& size);
	void handleDelete();
	void handleIconDrag(FileIcon* icon, const ImVec2& size);
	void onEntitySelected(void* data);
};

} // namespace

#endif
