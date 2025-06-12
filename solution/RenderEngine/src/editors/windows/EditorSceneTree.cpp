#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorSceneTree.h"
#include "SingletonsManager.h"
#include "ScenesManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "EngineValues.h"
#include "EditorsController.h"

#include "imgui.h"

namespace sre
{

EditorSceneTree::EditorSceneTree(ScenesManager* arg_scenesManager, EditorsController* arg_controller)
{
	Action* action = new Action{ [&](void* message) { this->onEntitySelected(message); } };
	this->selectionAction = SPTR<Action>(action);
}

void EditorSceneTree::onInit()
{
	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	
	MessagesManager* messagesManager = singletonsManager->get<MessagesManager>();
	messagesManager->addListener<EntitySelectionMessage>(this->selectionAction.get());
	this->selectedEntity = nullptr;

	ScenesManager* scenesManager = singletonsManager->get<ScenesManager>();
	this->scene = scenesManager->getScene();
	this->guiScene = scenesManager->getGuiScene();
}

void EditorSceneTree::onEditorGUI()
{
	ImGui::Begin("Hierarchy");

	this->drawScene(this->scene);
	this->drawScene(this->guiScene);
	
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
	{
		this->controller->notifyEntitySelection(nullptr);
	}

	if (ImGui::IsKeyPressed(ImGuiKey_Delete, false) && (this->selectedEntity != nullptr))
	{
		this->selectedEntity->destroy();
		this->controller->notifyEntitySelection(nullptr);
	}

	ImGui::End();
}

void EditorSceneTree::onCleanUp()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->removeListener<EntitySelectionMessage>(this->selectionAction.get());
}

void EditorSceneTree::drawScene(AScene* scene)
{
	if (scene && !scene->entities.empty())
	{
		if (ImGui::CollapsingHeader(scene->label.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			for (const auto& item : scene->entities)
				this->drawEntityTree(item.second.get(), 0);
		}
	}
}

void EditorSceneTree::drawEntityTree(Entity* entity, int index)
{
	const char* name = entity->getName();
	const size_t childrenCount = entity->getChildrenCount();
	const ImGuiTreeNodeFlags BASE_FLAGS = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;

	if (childrenCount == 0)
	{
		if (ImGui::Selectable(name, entity == this->selectedEntity, ImGuiSelectableFlags_SpanAllColumns))
		{
			this->controller->notifyEntitySelection(entity);
		}

		if (ImGui::BeginPopupContextItem())
		{
			this->controller->notifyEntitySelection(entity);

			ImGui::Text("[%s]", name);
			if (!this->selectedEntity->isAsset())
			{
				if (ImGui::Button("Save new Entity Asset"))
				{
					this->controller->saveEntity(this->selectedEntity);
					ImGui::CloseCurrentPopup();
				}
			}
			else if (!this->selectedEntity->isStored())
			{
				if (ImGui::Button("Save Entity Asset"))
				{
					this->controller->saveEntity(this->selectedEntity);
					ImGui::CloseCurrentPopup();
				}
			}
			if (ImGui::Button("Delete"))
			{
				this->selectedEntity->destroy();
				this->controller->notifyEntitySelection(nullptr);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
	else
	{
		ImGuiTreeNodeFlags flags = BASE_FLAGS;
		if (entity == this->selectedEntity)
		{
			flags |= ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_Selected;
		}

		bool open = ImGui::TreeNodeEx(reinterpret_cast<void*>(entity), flags, name);

		if (ImGui::IsItemClicked())
		{
			this->controller->notifyEntitySelection(entity);
		}

		if (open)
		{
			for (uint32_t i = 0; i < childrenCount; i++)
			{
				drawEntityTree(entity->getChild(i), i);
			}
			ImGui::TreePop();
		}
	}
}

void EditorSceneTree::onEntitySelected(void* data)
{
	EntitySelectionMessage* message = static_cast<EntitySelectionMessage*>(data);
	this->selectedEntity = message->entity;
}

} // namespace

#endif
