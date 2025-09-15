#include "MaterialEditorProperty.h"
#include "Material.h"
#include "AMaterialComponent.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "MaterialLoader.h"

#include "imgui.h"
#include "rapidyaml.hpp"

namespace sre
{

MaterialEditorProperty::MaterialEditorProperty(const char* title, ABaseMaterial** arg_value)
	: AEditorProperty(title)
{
	this->value = arg_value;
}

void MaterialEditorProperty::draw()
{
	AEditorProperty::draw();
	drawSubProperties();
}

void MaterialEditorProperty::onDraw()
{
	ImGui::Text((*this->value)->filePath.c_str());

	if (ImGui::BeginPopupContextItem("Save Material"))
	{
		ImGui::Text("[%s]", this->title.c_str());
		if (ImGui::MenuItem("Save"))
		{
			MaterialLoader().save((*this->value), (*this->value)->filePath.c_str());
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE"))
		{
			const char* filePath = static_cast<const char*>(payload->Data);
			if (filePath != nullptr)
			{
				this->reloadMaterial(filePath);
			}
		}
		ImGui::EndDragDropTarget();
	}
}

void MaterialEditorProperty::drawSubProperties()
{
	for (const auto& property : (*this->value)->editorProperties)
	{
		property->draw();
	}

	if ((*this->value)->isStandard())
	{
		Material** standardMaterial = reinterpret_cast<Material**>(this->value);
		for (const auto& component : (*standardMaterial)->componentsMap)
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

void MaterialEditorProperty::reloadMaterial(const char* filePath)
{
	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	assetsManager->releaseMaterial(*this->value);
	*this->value = assetsManager->loadMaterial(filePath);
	
	this->onPropertyChanged();
}

} // namespace
