#if !defined(__ANDROID__)

#include "EditorSceneTree.h"
#include "SingletonsManager.h"
#include "ScenesManager.h"
#include "EngineValues.h"
#include "EditorsController.h"
#include "GuizmoComponent.h"

#include "imgui.h"

namespace sre
{

EditorSceneTree::EditorSceneTree(EditorsController* arg_controller)
	: controller(arg_controller)
{ }

void EditorSceneTree::onInit()
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	ScenesManager* scenesManager = singletonsManager->get<ScenesManager>();
	this->scene = scenesManager->getScene();
	this->guiScene = scenesManager->getGuiScene();
}

void EditorSceneTree::onEditorGUI()
{
	ImGui::Begin("Hierarchy");

	this->drawScene(this->scene);
	this->drawScene(this->guiScene);
	
	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		this->controller->setSelectedEntity(nullptr);
	}

	Entity* selectedEntity = this->controller->getSelectedEntity();
	if (selectedEntity)
	{
		if (ImGui::IsKeyPressed(ImGuiKey_Delete, false))
		{
			selectedEntity->destroy();
			this->controller->setSelectedEntity(nullptr);
		}

		if (ImGui::IsKeyPressed(ImGuiKey_D, false) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
		{
			this->controller->duplicateSelectedEntity();
		}
	}

	ImGui::End();
}

void EditorSceneTree::drawScene(AScene* scene)
{
	if (scene && !scene->entities.empty())
	{
		if (ImGui::CollapsingHeader(scene->label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			for (const auto& item : scene->entities)
			{
				this->drawEntityTree(scene, item.second.get(), 0);
			}
		}
	}
}

void EditorSceneTree::drawEntityTree(AScene* scene, Entity* entity, int index)
{
	if (entity->dontShowInEditorSceneTree)
	{
		return;
	}

	const char* name = entity->getName();
	size_t childrenCount = entity->getChildrenCount();

	Entity* selectedEntity = this->controller->getSelectedEntity();

	if (childrenCount == 0)
	{
		if (ImGui::Selectable(name, entity == selectedEntity, ImGuiSelectableFlags_SpanAllColumns))
		{
			this->controller->setSelectedEntity(entity);
		}

		this->drawContextualMenu(selectedEntity, entity, name);
		this->handleDragAndDrop(scene, entity);
	}
	else
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (entity == selectedEntity)
		{
			flags |= ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_Selected;
		}

		bool open = ImGui::TreeNodeEx(reinterpret_cast<void*>(entity), flags, name);

		if (ImGui::IsItemClicked())
		{
			this->controller->setSelectedEntity(entity);
		}

		this->drawContextualMenu(selectedEntity, entity, name);
		this->handleDragAndDrop(scene, entity);

		if (open)
		{
			for (uint32_t i = 0; i < entity->getChildrenCount(); i++)
			{
				drawEntityTree(scene, entity->getChild(i), i);
			}
			ImGui::TreePop();
		}
	}
}

void EditorSceneTree::drawContextualMenu(Entity* selectedEntity, Entity* entity, const char* name)
{
	if (ImGui::BeginPopupContextItem())
	{
		this->controller->setSelectedEntity(entity);

		ImGui::Text("[%s]", name);
		if (!selectedEntity->isAsset())
		{
			if (ImGui::MenuItem("Save new Entity Asset"))
			{
				this->controller->saveEntity(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
		}
		else if (!selectedEntity->isStored())
		{
			if (ImGui::MenuItem("Save Entity Asset"))
			{
				this->controller->saveEntity(selectedEntity);
				ImGui::CloseCurrentPopup();
			}
		}
		if (ImGui::MenuItem("Delete"))
		{
			selectedEntity->destroy();
			this->controller->setSelectedEntity(nullptr);
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

void EditorSceneTree::handleDragAndDrop(AScene* scene, Entity* entity)
{
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("ENTITY", &entity, sizeof(Entity*));
		ImGui::Text("%s", entity->getName());
		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY"))
		{
			Entity* sourceEntity = *(Entity**)payload->Data;
			if (sourceEntity != nullptr && sourceEntity != entity)
			{
				Entity* parent = sourceEntity->getParent();
				if (parent)
				{
					UPTR<Entity> movedEntity = parent->moveChild(sourceEntity->getName());
					entity->addChild(std::move(movedEntity));
				}
				else
				{
					scene->moveEntityToBeChild(sourceEntity->getName(), entity);
				}
			}
		}
		ImGui::EndDragDropTarget();
	}
}

} // namespace

#endif
