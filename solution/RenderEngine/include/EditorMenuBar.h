#if defined(DEBUG) && !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"

namespace sre
{

class EditorsController;

class EditorMenuBar : public IEditorWindow
{
private:
	bool* isDemoEnabled;
	EditorsController* controller;

	const char* CUBE_MESH_PATH = "engine\\media\\Cube.mesh";
	const char* SPHERE_MESH_PATH = "engine\\media\\Sphere.mesh";
	const char* CONE_MESH_PATH = "engine\\media\\Cone.mesh";
	const char* CYLINDER_MESH_PATH = "engine\\media\\Cylinder.mesh";
	const char* TORUS_MESH_PATH = "engine\\media\\Torus.mesh";
	const char* PLANE_MESH_PATH = "engine\\media\\Plane.mesh";

public:
	EditorMenuBar(bool* demoEnabled, EditorsController* arg_controller);

	void onEditorGUI() override;

private:
	void drawFileGroup();
	void drawEditGroup();
	void drawEntitiesGroup();
	void drawHelpGroup();
	void exitEditor();
};

} // namespace

#endif
