#include "MaterialEditorProperty.h"
#include "Material.h"
#include "AMaterialComponent.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "MaterialLoader.h"

#include <imgui/imgui.h>
#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

MaterialEditorProperty::MaterialEditorProperty(const char* title, Material** arg_material)
	: AEditorProperty(title), material(arg_material)
{ }

void MaterialEditorProperty::draw()
{
	ImGui::PushID(this->title.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->title.c_str());

	ImGui::NextColumn();
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text((*this->material)->fileName.c_str());

	ImGui::Columns(1);

	if (ImGui::BeginPopupContextItem("Save Popup"))
	{
		ImGui::Text("[%s]", this->title.c_str());
		if (ImGui::Button("Save"))
		{
			MaterialLoader().save((*this->material), (*this->material)->fileName.c_str());
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	ImGui::PopID();

	for (const auto& property : (*this->material)->editorProperties)
	{
		property->draw();
	}

	for (const auto& component : (*this->material)->componentsMap)
	{
		const char* componentName = component.second->getClassName();
		if (ImGui::TreeNodeEx(componentName, ImGuiTreeNodeFlags_DefaultOpen))
		{
			for (const auto& property : component.second->editorProperties)
			{
				property->draw();
			}
			// XXX ImGui::Separator();
			ImGui::TreePop();
		}
	}
}

void MaterialEditorProperty::serialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode << (*this->material)->fileName;
}

void MaterialEditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
	std::string fileName;
	propertyNode >> fileName;

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	*this->material = assetsManager->loadMaterial(fileName.c_str());
}

} // namespace
