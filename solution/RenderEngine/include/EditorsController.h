#pragma once

#include "memory_aliases.h"
#include "FileIcon.h"

#include <string>

namespace sre
{

class ScenesManager;
class Scene;
class Entity;

class EditorsController
{
private:
	std::string currentDirectory;
	ScenesManager* scenesManager{ nullptr };
	Entity* selectedEntity{ nullptr };

	const char* DEFAULT_GUI_IMAGE_PATH	= "engine/media/textures/whiteTexture.png";
	const char* DEFAULT_TEXT_FONT_PATH	= "engine/media/fonts/verdana";
	const char* DEFAULT_SCENE_PATH		= "engine/scenes/Default.scene";
	const char* DEFAULT_GUI_SCENE_PATH	= "engine/scenes/DefaultGui.gui";
	const char* DEFAULT_ENTITY_PATH		= "engine/media/DefaultEntity.ent";
	const char* DEFAULT_MATERIAL_PATH	= "engine/media/DefaultMaterial.mat";

public:
	EditorsController(ScenesManager* arg_scenesManager);
	void newScene();
	void openScene();
	void openGui();
	void saveScene();
	void saveGui();
	void createGUIImage();
	void createGUIText();
	void refreshFileIcons(std::vector<UPTR<FileIcon>>& result);
	void saveEntity(Entity* entity);
	void loadFileFromBrowser(const std::string& filePath);
	void importMesh(const char* sourceFilePath, const char* destinationPath, float scaleFactor, bool importMaterials, std::string& resultFilePath);
	void copyFileToCurrentDirectory(const std::string& sourceFilePath, const std::string& destinationFileName = "");
	Entity* createMeshEntity(const std::string& filePath, const char* meshName);
	void createDirectionalLight();
	void createPointLight();
	void setSelectedEntity(Entity* entity);
	Entity* getSelectedEntity();
	void deleteFile(const char* filePath);
	void duplicateFile(const std::string& filePath);
	void loadMaterialToEntity(Entity* entity, const std::string& materialFilePath);
	void createScene();
	void createStoredEntity();
	void createMaterial();
	void notifyRefreshFileIcons();
	std::string getCurrentDirectory() const;
	void setCurrentDirectory(const std::string& directory);
	void tryLoadMaterialToEntity(Entity* entity, const std::string& entityPath);
	void createFolderInCurrentDirectory();
};

} // namespace
