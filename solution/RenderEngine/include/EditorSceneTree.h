#if !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"
#include "memory_aliases.h"
#include "InputTextHandler.h"

namespace sre
{

class ScenesManager;
class AScene;
class Entity;
class EditorsController;

class EditorSceneTree : public IEditorWindow
{
private:
	AScene* scene{ nullptr };
	AScene* guiScene{ nullptr };
	EditorsController* controller{ nullptr };
	InputTextHandler inputTextHandler;

public:
	EditorSceneTree(EditorsController* arg_controller);
	void onInit() override;
	void onEditorGUI() override;

private:
	void drawScene(AScene* scene);
	void drawEntityTree(AScene* scene, Entity* entity, int index, bool& entityMoved);
	void drawContextualMenu(Entity* selectedEntity, Entity* entity, const std::string& name);
	bool handleDragAndDrop(AScene* scene, Entity* entity);
	void handleDropToRoot(AScene* scene);
	void handleDeleteItem(Entity* selectedEntity);
	void handleDuplicateItem(Entity* selectedEntity);
	void handleItemRenaming(Entity* selectedEntity);
};

} // namespace

#endif
