#include "FileBrowserPathButtons.h"
#include "EditorsController.h"
#include "FileUtils.h"

#include "imgui.h"

namespace sre
{

void FileBrowserPathButtons::onInit(EditorsController* arg_controller)
{
	this->controller = arg_controller;
	this->gameButtons.clear();
	this->engineButtons.clear();

	this->gameButtons.push_back({ "Game", FileUtils::getContentAbsolutePath("game") });
	this->engineButtons.push_back({ "Engine", FileUtils::getContentAbsolutePath("engine") });

	this->controller->setCurrentDirectory(this->gameButtons.begin()->path);
}

void FileBrowserPathButtons::onEditorGUI()
{
	this->drawButtons(this->gameButtons);
	this->drawButtons(this->engineButtons);
}

void FileBrowserPathButtons::onFolderOpen(const std::string& newPath)
{
	this->currentButtons->push_back({ FileUtils::getFileName(newPath), newPath });
	this->controller->setCurrentDirectory(newPath);
}

void FileBrowserPathButtons::drawButtons(std::vector<PathButton>& buttons)
{
	std::vector<PathButton>::iterator it = buttons.begin();
	while (it != buttons.end())
	{
		PathButton& button = *it;
		if (ImGui::SmallButton(button.name.c_str()))
		{
			this->controller->setCurrentDirectory(button.path);
			this->currentButtons = &buttons;
			break;
		}
		ImGui::SameLine();
		ImGui::Text("/");
		ImGui::SameLine();

		++it;
	}
	ImGui::NewLine();

	if (it != buttons.end())
	{
		buttons.erase(it + 1, buttons.end());
	}
}

} // namespace
