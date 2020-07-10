#include "WorldEditor.h"

#include "thirdParties/imgui/imgui.h"

namespace sre
{

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
		for (int i = 0; i < 5; i++)
		{
			if (ImGui::TreeNode((void*)(intptr_t)i, "Entity %d", i))
			{
				ImGui::BulletText("Child %d", i);
				ImGui::TreePop();
			}
		}
		ImGui::BulletText("Entity 6");
		ImGui::BulletText("Entity 7");
		
		ImGui::TreePop();
	}
	
	ImGui::End();
}

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
