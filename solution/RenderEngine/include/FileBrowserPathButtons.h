#pragma once

#include <string>
#include <vector>

namespace sre
{

struct PathButton
{
	std::string name;
	std::string path;
};

class FileBrowserPathButtons
{
private:
	std::vector<PathButton> gameButtons;
	std::vector<PathButton> engineButtons;
	std::vector<PathButton>* currentButtons{ &gameButtons };

	class EditorsController* controller{ nullptr };

public:
	void onInit(class EditorsController* arg_controller);
	void onEditorGUI();
	void onFolderOpen(const std::string& newPath);

private:
	void drawButtons(std::vector<PathButton>& buttons);
};

} // namespace
