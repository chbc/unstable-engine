#if !defined(__ANDROID__)

#include "EditorMenuBar.h"
#include "MessagesManager.h"
#include "SingletonsManager.h"
#include "EditorMessages.h"
#include "EditorsController.h"

#include "imgui.h"

namespace sre
{

#define MENU_ITEM(label, method)	\
	if (ImGui::MenuItem(label))	\
	{								\
		this->controller->method();	\
	}

#define CREATE_MESH_ITEM(filePath, meshName)	\
	if (ImGui::MenuItem(meshName))	\
	{								\
		this->controller->createMeshEntity(filePath, meshName);	\
	}

EditorMenuBar::EditorMenuBar(bool* demoEnabled, EditorsController* arg_controller)
	: isDemoEnabled(demoEnabled), controller(arg_controller)
{
}

void EditorMenuBar::onEditorGUI()
{
	if (ImGui::BeginMenuBar())
	{
		this->drawFileGroup();
		this->drawEditGroup();
		this->drawEntitiesGroup();
		this->drawHelpGroup();

		ImGui::EndMenuBar();
	}

	if (ImGui::IsKeyPressed(ImGuiKey_Escape, false) ||
		ImGui::IsKeyPressed(ImGuiKey_Home, false)
	)
	{
		exitEditor();
	}
}

void EditorMenuBar::drawFileGroup()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::BeginMenu("Scene"))
		{
			MENU_ITEM("New scene", newScene);
			MENU_ITEM("Open Scene", openScene);
			MENU_ITEM("Save Scene", saveScene);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("GUI"))
		{
			ImGui::MenuItem("New GUI");

			MENU_ITEM("Open GUI", openGui);
			MENU_ITEM("Save GUI", saveGui);

			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Exit"))
		{
			this->exitEditor();
		}

		ImGui::EndMenu();
	}
}

void EditorMenuBar::drawEditGroup()
{
	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::MenuItem("Preferences");
		ImGui::EndMenu();
	}
}

void EditorMenuBar::drawEntitiesGroup()
{
	if (ImGui::BeginMenu("Entities"))
	{
		if (ImGui::BeginMenu("Basic Shapes"))
		{
			CREATE_MESH_ITEM(CUBE_MESH_PATH, "Cube");
			CREATE_MESH_ITEM(SPHERE_MESH_PATH, "Sphere");
			CREATE_MESH_ITEM(CONE_MESH_PATH, "Cone");
			CREATE_MESH_ITEM(CYLINDER_MESH_PATH, "Cylinder");
			CREATE_MESH_ITEM(TORUS_MESH_PATH, "Torus");
			CREATE_MESH_ITEM(PLANE_MESH_PATH, "Plane");

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("GUI"))
		{
			MENU_ITEM("Image", createGUIImage);
			MENU_ITEM("Text", createGUIText);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Lights"))
		{
			MENU_ITEM("Directional Light", createDirectionalLight);
			MENU_ITEM("Point Light", createPointLight);
			MENU_ITEM("Skybox", createSkybox);

			ImGui::EndMenu();
		}

		ImGui::EndMenu();
	}
}

void EditorMenuBar::drawHelpGroup()
{
	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("ImGui Demo"))
			*this->isDemoEnabled = true;

		ImGui::MenuItem("About");
		ImGui::EndMenu();
	}
}

void EditorMenuBar::exitEditor()
{
	MessagesManager* messagesManager = SingletonsManager::getInstance()->get<MessagesManager>();
	ExitEditorMessage message;
	messagesManager->notify(&message);
}

} // namespace

#endif
