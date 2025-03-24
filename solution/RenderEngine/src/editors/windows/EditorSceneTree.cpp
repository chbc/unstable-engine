#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorSceneTree.h"
#include "SingletonsManager.h"
#include "ScenesManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "EngineValues.h"
#include "EditorsController.h"

#include "imgui/imgui.h"

namespace sre
{

EditorSceneTree::EditorSceneTree(ScenesManager* arg_scenesManager, EditorsController* arg_controller)
	: scenesManager(arg_scenesManager), selectedEntity(nullptr), controller(arg_controller)
{
	Action* action = new Action{ [&](void* message) { this->onEntitySelected(message); } };
	this->selectionAction = SPTR<Action>(action);
}

void EditorSceneTree::onInit()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	messagesManager->addListener<EntitySelectionMessage>(this->selectionAction.get());
	this->selectedEntity = nullptr;
}

void EditorSceneTree::onEditorGUI()
{
	ImGui::Begin("Hierarchy");

	this->drawScene(this->scenesManager->scene.get());
	this->drawScene(this->scenesManager->guiScene.get());
	
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
	{
		this->notifySelection(nullptr);
	}

	if (ImGui::IsKeyPressed(ImGuiKey_Delete, false) && (this->selectedEntity != nullptr))
	{
		this->selectedEntity->destroy();
		this->notifySelection(nullptr);
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
		if (ImGui::CollapsingHeader(scene->name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
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
			this->notifySelection(entity);
		}

		if (ImGui::BeginPopupContextItem())
		{
			this->notifySelection(entity);

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
				this->notifySelection(nullptr);
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

		if (!entity->isSaved())
		{
			flags |= ImGuiTreeNodeFlags_Framed;
		}

		bool open = ImGui::TreeNodeEx(reinterpret_cast<void*>(entity), flags, name);

		if (ImGui::IsItemClicked())
		{
			this->notifySelection(entity);
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

void EditorSceneTree::notifySelection(Entity* entity)
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	EntitySelectionMessage message{ entity };
	messagesManager->notify(&message);
}

void EditorSceneTree::onEntitySelected(void* data)
{
	EntitySelectionMessage* message = static_cast<EntitySelectionMessage*>(data);
	this->selectedEntity = message->entity;
}

} // namespace

#endif
