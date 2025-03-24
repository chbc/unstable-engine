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

MaterialEditorProperty::MaterialEditorProperty(const char* title, Material** arg_value)
	: AEditorProperty(title), value(arg_value)
{ }

void MaterialEditorProperty::draw()
{
	AEditorProperty::draw();
	drawSubProperties();
}

void MaterialEditorProperty::onDraw()
{
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text((*this->value)->filePath.c_str());

	ImGui::Columns(1);

	if (ImGui::BeginPopupContextItem("Save Popup"))
	{
		ImGui::Text("[%s]", this->title.c_str());
		if (ImGui::Button("Save"))
		{
			MaterialLoader().save((*this->value), (*this->value)->filePath.c_str());
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

void MaterialEditorProperty::drawSubProperties()
{
	for (const auto& property : (*this->value)->editorProperties)
	{
		property->draw();
	}

	for (const auto& component : (*this->value)->componentsMap)
	{
		const char* componentName = component.second->getClassName();
		if (ImGui::TreeNodeEx(componentName, ImGuiTreeNodeFlags_DefaultOpen))
		{
			for (const auto& property : component.second->editorProperties)
			{
				property->draw();
			}
			ImGui::TreePop();
		}
	}
}


void MaterialEditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode << (*this->value)->filePath;
}

void MaterialEditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	std::string filePath;
	propertyNode >> filePath;

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	*this->value = assetsManager->loadMaterial(filePath.c_str());
}

void MaterialEditorProperty::copy(AEditorProperty* destination)
{
	MaterialEditorProperty* derivedProperty = static_cast<MaterialEditorProperty*>(destination);

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	*derivedProperty->value = assetsManager->loadMaterial((*this->value)->filePath.c_str());
}

} // namespace
