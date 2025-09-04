#pragma once

#include "memory_aliases.h"
#include "ImportMeshPopup.h"

#include <functional>

namespace sre
{

class EditorsController;
class EditorFileBrowser;

using Action = std::function<void(void*)>;

class ExternalFileDropHandler
{
private:
	EditorsController* controller{ nullptr };
	EditorFileBrowser* fileBrowser{ nullptr };
	SPTR<Action_OnClosePopup> onClosePopupAction;
	SPTR<Action> externalFileDropAction;

public:
	ExternalFileDropHandler();
	void onInit(EditorsController* arg_controller, EditorFileBrowser* arg_fileBrowser);
	void onCleanUp();

private:
	void handleExternalFileDrop(void* message);
	void handleImportMesh(const std::string& sourceFilePath);
	void handleCopyFile(const std::string& sourceFilePath);
};

} // namespace sre
