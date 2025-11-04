#include "InputTextHandler.h"

#include "imgui/imgui.h"

namespace sre
{

static int FilterItemNameCallback(ImGuiInputTextCallbackData* data)
{
	if (data->EventFlag == ImGuiInputTextFlags_CallbackCharFilter)
	{
		if (strchr("<>:\"/\\|?*", data->EventChar))
		{
			return 1;
		}
	}

	return 0;
}

bool InputTextHandler::isRenaming(const std::string& itemName) const
{
	return (itemName == this->itemToRename);
}

bool InputTextHandler::inputText(std::string& itemName)
{
	bool result = false;

	ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCharFilter;
	char buffer[128];
	memset(buffer, 0, sizeof(buffer));
	strncpy(buffer, itemName.c_str(), sizeof(buffer) - 1);
	ImGui::SetKeyboardFocusHere();
	if (ImGui::InputText("##RenameInput", buffer, IM_ARRAYSIZE(buffer), flags, FilterItemNameCallback))
	{
		itemName = std::string(buffer);
		this->itemToRename = "";
		result = true;
	}

	return result;
}

void InputTextHandler::setItemToRename(const std::string& itemName)
{
	this->itemToRename = itemName;
}

} // namespace
