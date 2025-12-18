#if !defined(__ANDROID__)
#pragma once

#include "IEditorWindow.h"
#include "FileIcon.h"
#include "memory_aliases.h"
#include "ExternalFileDropHandler.h"
#include "FileBrowserContextMenu.h"
#include "InputTextHandler.h"
#include "FileBrowserPathButtons.h"

#include <vector>
#include <functional>

namespace sre
{

class EditorsController;

class EditorFileBrowser : public IEditorWindow
{
private:
	ExternalFileDropHandler externalFileDropHandler;
	FileBrowserContextMenu contextMenu;
	std::vector<UPTR<FileIcon>> fileIcons;
	SPTR<Action> entitySelectionAction;
	SPTR<Action> refreshIconsAction;
	SPTR<Action> startRenamingFileAction;
	EditorsController* controller{ nullptr };
	FileIcon* selectedItem{ nullptr };
	InputTextHandler inputTextHandler;
	FileBrowserPathButtons pathButtons;

public:
	EditorFileBrowser(EditorsController* arg_controller);
	void onInit() override;
	void onEditorGUI() override;
	void onCleanUp() override;
	void refreshFileIcons();

private:
	void setupColumns(const ImVec2& iconSize);
	void drawIcon(FileIcon* icon, const ImVec2& size);
	bool drawLabel(FileIcon* icon);
	void handleDelete();
	void handleDuplicate();
	void handleIconDrag(FileIcon* icon, const ImVec2& size);
	void handleFileRenaming();
	void onEntitySelected(void* data);
	void onStartRenamingFile(void* data);
};

} // namespace

#endif
