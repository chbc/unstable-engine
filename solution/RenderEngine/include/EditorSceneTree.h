#if !defined(__ANDROID__)

#pragma once

#include "IEditorWindow.h"
#include "memory_aliases.h"
#include "InputTextHandler.h"

#include <functional>

namespace sre
{

class ScenesManager;
class AScene;
class Entity;
using Action = std::function<void(void*)>;
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
	void drawEntityTree(AScene* scene, Entity* entity, int index);
	void drawContextualMenu(Entity* selectedEntity, Entity* entity, const std::string& name);
	void handleDragAndDrop(AScene* scene, Entity* entity);
	void handleDropToRoot(AScene* scene);
	void handleDeleteItem(Entity* selectedEntity);
	void handleDuplicateItem(Entity* selectedEntity);
	void handleItemRenaming(Entity* selectedEntity);
};

} // namespace

#endif
