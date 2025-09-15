#pragma once

namespace sre
{

class FileBrowserContextMenu
{
private:
	class EditorsController* controller{ nullptr };

public:
	void onInit(EditorsController* arg_controller);
	void onEditorGUI();
};

} // namespace
