#include "SceneLoader.h"
#include "FileUtils.h"
#include "AScene.h"
#include "EntityParser.h"
#include "Paths.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"

namespace sre
{

void SceneLoader::save(AScene* scene, const char* sceneName)
{
	c4::yml::Tree tree;
	c4::yml::NodeRef root = tree.rootref();

	root |= ryml::MAP;
	for (const auto& entityItem : scene->entities)
	{
		c4::yml::NodeRef entityNode = root[entityItem.first.c_str()];
		EntityParser::serialize(entityNode, entityItem.second.get());
	}

	std::string filePath;
	Paths().buildSceneFilePath(EContentType::CONTENT, sceneName, filePath);
	std::string content = c4::yml::emitrs_yaml<std::string>(tree);
	FileUtils::saveFile(filePath, content);
}

void SceneLoader::load(AScene* scene, const char* sceneName)
{
	std::string fileContent;
	std::string filePath;
	Paths().buildSceneFilePath(EContentType::CONTENT, sceneName, filePath);
	FileUtils::loadFile(filePath, fileContent);

	c4::yml::Tree tree = c4::yml::parse_in_place(c4::to_substr(fileContent));

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	c4::yml::ConstNodeRef root = tree.crootref();
	for (c4::yml::ConstNodeRef entityNode : root.children())
	{
		std::ostringstream nameStream;
		nameStream << entityNode.key();
		std::string name = nameStream.str();

		if (entityNode.has_child("FileName"))
		{
			std::string fileName;
			entityNode["FileName"] >> fileName;
			Entity* entity = assetsManager->loadEntity(fileName.c_str(), name);
			scene->addEntityAsset(entity);
		}
		else
		{
			Entity* entity = scene->createEntity(name);
			EntityParser::deserialize(entityNode, entity);
		}
	}
}

} // namespace sre
