#include "SceneLoader.h"
#include "FileUtils.h"
#include "AScene.h"
#include "EntityParser.h"
#include "Paths.h"

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
		serializeEntity(scene, entityNode, entityItem.second.get());
	}

	std::string filePath;
	Paths().buildSceneFilePath(sceneName, filePath, false);
	std::string content = c4::yml::emitrs_yaml<std::string>(tree);
	FileUtils::saveFile(filePath, content);
}

void SceneLoader::serializeEntity(AScene* scene, c4::yml::NodeRef& entityNode, Entity* entity)
{
	entityNode |= ryml::MAP;

	std::string className{ entity->getClassName() };
	if (className != "Entity")
	{
		entityNode["Class"] << className;
	}

	std::string fileName{ entity->fileName };
	bool modifiedOnly = false;
	if (!fileName.empty())
	{
		entityNode["FileName"] << fileName;
		modifiedOnly = true;
	}
		
	EntityParser::serialize(entityNode, entity, modifiedOnly);
}

void SceneLoader::load(AScene* scene, const char* sceneName)
{
	std::string fileContent;
	std::string filePath;
	Paths().buildSceneFilePath(sceneName, filePath);
	FileUtils::loadFile(filePath, fileContent);

	c4::yml::Tree tree = c4::yml::parse_in_place(c4::to_substr(fileContent));
	c4::yml::ConstNodeRef root = tree.crootref();
	for (c4::yml::ConstNodeRef entityNode : root.children())
	{
		std::ostringstream nameStream;
		nameStream << entityNode.key();
		std::string name = nameStream.str();
		std::string fileName;
		std::string className{ "Entity" };

		if (entityNode.has_child("Class"))
		{
			entityNode["Class"] >> className;
		}
		if (entityNode.has_child("FileName"))
		{
			entityNode["FileName"] >> fileName;
		}

		Entity* entity = scene->createEntity(name, nullptr, className.c_str(), fileName.c_str());
		EntityParser::deserialize(entityNode, entity);
	}
}

} // namespace sre
