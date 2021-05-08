#if defined(DEBUG) && !defined(__ANDROID__)

#include "EditorEntityProperties.h"
#include "SingletonsManager.h"
#include "MessagesManager.h"
#include "EditorMessages.h"
#include "Entity.h"

#include "imgui/imgui.h"

namespace sre
{

EditorEntityProperties::EditorEntityProperties() : entity(nullptr)
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
	Action action = [&](void* message) { this->onEntitySelected(message); };
	messagesManager->addListener<EntitySelectionMessage>(action);
}

void EditorEntityProperties::onEditorGUI()
{
	if 
	(
		(this->entity != nullptr) &&
		ImGui::CollapsingHeader("Properties", ImGuiTreeNodeFlags_DefaultOpen)
	)
	{
		// https://en.cppreference.com/w/cpp/keyword/reflexpr
		for (const auto& component : this->entity->componentsMap)
		{
			const char* componentName = component.second->getClassName();
			if (ImGui::TreeNodeEx(componentName, ImGuiTreeNodeFlags_DefaultOpen))
			{
				for (const auto& variable : component.second->editorVariables)
				{
					switch (variable->typeId)
					{
						case TypeId::VEC3:
							this->drawVec3(variable);
							break;
					}
				}
				ImGui::Separator();
				ImGui::TreePop();
			}
		}

		/* XXX
		ImGui::Columns(2);
		ImGui::Separator();

		this->drawProperty("Position", "##position", this->position);

		ImGui::NextColumn();
		this->drawProperty("Rotation", "##rotation", this->rotation, -360, 360);

		ImGui::NextColumn();
		this->drawProperty("Scale", "##scale", this->scale, 0.001f);

		ImGui::Columns(1);
		ImGui::Separator();

		ImGui::TreePop();
		*/
	}
	ImGui::End();
}

void EditorEntityProperties::onRelease()
{
	this->entity = nullptr;
}

void EditorEntityProperties::drawVec3(const SPTR<EditorVariable>& editorVariable)
{
	glm::vec3* vector = static_cast<glm::vec3*>(editorVariable->pointer.get());
	float values[3] = { vector->x, vector->y, vector->z };

	ImGui::Columns(2);
	ImGui::Text(editorVariable->title.c_str());
	ImGui::NextColumn();
	ImGui::SetNextItemWidth(-1);
	ImGui::DragFloat3(editorVariable->label.c_str(), values, 0.1f, 0.0f, 0.0f, "%.1f");
	ImGui::Columns(1);
}

/*
void EditorEntityProperties::drawProperty(const char* title, const char* label, float* values, float min, float max)
{
	ImGui::Text(title);
	ImGui::NextColumn();
	ImGui::SetNextItemWidth(-1);
	if (ImGui::DragFloat3(label, values, 0.1f, min, max, "%.1f"))
	{
		this->entity->getTransform()->setPosition(glm::vec3(this->position[0], this->position[1], this->position[2]));
		this->entity->getTransform()->setRotation(this->rotation);
		this->entity->getTransform()->setScale(glm::vec3(this->scale[0], this->scale[1], this->scale[2]));
	}
}
*/

void EditorEntityProperties::onEntitySelected(void* data)
{
	EntitySelectionMessage* message = static_cast<EntitySelectionMessage*>(data);
	this->entity = message->entity;
}

} // namespace

#endif
