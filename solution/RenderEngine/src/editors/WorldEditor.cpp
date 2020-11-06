#include "WorldEditor.h"
#include "SceneManager.h"

#include "thirdParties/imgui/imgui.h"

#include "SingletonsManager.h"
#include "MessagesManager.h"

namespace sre
{

	struct XXX_Message
	{
		int a;
	};
	
void WorldEditor::init(SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;
	MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();

	Action action = [&](void* message) { this->XXX_MessageMethod(message); };
	messagesManager->addListener<XXX_Message>(action);
}

void WorldEditor::XXX_MessageMethod(void* message)
{
	XXX_Message* aMessage = static_cast<XXX_Message*>(message);
}

void WorldEditor::onGUI(bool* enabled) const
{
	this->drawMenu(enabled);
	this->drawEntitiesWindow();
	this->drawSceneTreeWindow();
	this->drawPropertiesWindow();
	this->drawMediaWindow();
}

void WorldEditor::drawMenu(bool* enabled) const
{
	static bool showDemo = false;

	if (showDemo)
		ImGui::ShowDemoWindow(&showDemo);

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(1024, 10));

	ImGui::Begin
	(
		"Menu", nullptr,
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoMove
	);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("New scene");
			ImGui::MenuItem("Open scene");
			ImGui::MenuItem("Save scene");
			ImGui::MenuItem("Save scene as");
			if (ImGui::MenuItem("Exit"))
				*enabled = false;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("Preferences");
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("ImGui Demo"))
				showDemo = true;

			ImGui::MenuItem("About");
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
	ImGui::End();
}

void WorldEditor::drawEntitiesWindow() const
{
	ImGui::SetNextWindowPos(ImVec2(0.0f, 19.0f), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(150.0f, 598.0f), ImGuiCond_Once);

	ImGui::Begin("Entities");
	ImGui::End();
}

void WorldEditor::drawSceneTreeWindow() const
{
	ImGui::SetNextWindowPos(ImVec2(854.0f, 19.0f), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(170.0f, 375.0f), ImGuiCond_Once);

	ImGui::Begin("Scene Tree");
	
	if (ImGui::TreeNodeEx("scene_name", ImGuiTreeNodeFlags_DefaultOpen))
	{
		int index = 0;
		for (const auto& item : this->sceneManager->entities)
		{
			if (item.second->getChildrenCount() == 0)
				ImGui::TreeNodeEx("entity", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, item.first.c_str());
			else if (ImGui::TreeNode(reinterpret_cast<void*>(static_cast<intptr_t>(index)), item.first.c_str()))
			{
				this->drawEntityTree(item.second.get(), index);
				ImGui::TreePop();
			}
		}
		
		ImGui::TreePop();
	}
	
	ImGui::End();
}

void WorldEditor::drawEntityTree(Entity* entity, int index) const
{
	const char* name = entity->getName();
	const uint32_t childrenCount = entity->getChildrenCount();
	
	if (childrenCount == 0)
	{
		ImGui::TreeNodeEx("entity", ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen, name);
	}
	else if (ImGui::TreeNode(reinterpret_cast<void*>(static_cast<intptr_t>(index)), name))
	{
		for (int i = 0; i < childrenCount; i++)
		{
			drawEntityTree(entity->getChild(i), i);
		}
		ImGui::TreePop();
	}
}

bool yeah = false;
	
void WorldEditor::drawPropertiesWindow() const
{
	ImGui::SetNextWindowPos(ImVec2(854.0f, 394.0f), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(170.0f, 374.0f), ImGuiCond_Once);

	ImGui::Begin("Properties");

	if (ImGui::TreeNode("Transform"))
	{
		ImGui::Columns(2);
		ImGui::Separator();

		static float position[3] = { 0.0f, 0.0f, 0.0f };
		static float rotation[3] = { 0.0f, 0.0f, 0.0f };
		static float scale[3] = { 1.0f, 1.0f, 1.0f };

		ImGui::Text("Position");
		ImGui::NextColumn();
		ImGui::SetNextItemWidth(-1);
		ImGui::DragFloat3("##position", position, 0.1f, 0, 0, "%.1f");

		ImGui::NextColumn();
		ImGui::Text("Rotation");
		ImGui::NextColumn();
		ImGui::SetNextItemWidth(-1);
		ImGui::DragFloat3("##rotation", rotation, 0.1f, -360, 360, "%.1f");

		ImGui::NextColumn();
		ImGui::Text("Scale");
		ImGui::NextColumn();
		ImGui::SetNextItemWidth(-1);
		ImGui::DragFloat3("##scale", scale, 0.1f, 0, 0, "%.1f");

		ImGui::Columns(1);
		ImGui::Separator();

		ImGui::TreePop();

		// ### TESTE DE NOTIFICAÇÃO
		if (!yeah)
		{
			MessagesManager* messagesManager = SingletonsManager::getInstance()->resolve<MessagesManager>();
			UPTR<XXX_Message> message = make_unique<XXX_Message>();
			message->a = 15;
			messagesManager->notify(message.get());

			yeah = true;
		}
	}
	ImGui::End();
}

void WorldEditor::drawMediaWindow() const
{
	ImGui::SetNextWindowPos(ImVec2(0.0f, 618.0f), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(854.0f, 150.0f), ImGuiCond_Once);

	ImGui::Begin("Media");
	ImGui::End();
}

} // namespace
