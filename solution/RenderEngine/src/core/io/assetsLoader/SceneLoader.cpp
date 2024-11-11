#include "SceneLoader.h"
#include "FileUtils.h"
#include "AScene.h"
#include "EntityParser.h"

namespace sre
{

#ifdef __ANDROID__
	const std::string BASE_FOLDER = "scenes/es/";
#else
	const std::string BASE_FOLDER = "../../scenes/";
#endif

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

	std::string filePath = BASE_FOLDER + sceneName + std::string{ ".scene" };
	std::string content = c4::yml::emitrs_yaml<std::string>(tree);
	FileUtils::saveFile(filePath, content);
}

void SceneLoader::load(AScene* scene, const char* sceneName)
{
	std::string fileContent;
	std::string filePath = BASE_FOLDER + sceneName + std::string{ ".scene" };
	FileUtils::loadFile(filePath, fileContent);

	c4::yml::Tree tree = c4::yml::parse_in_place(c4::to_substr(fileContent));

	c4::yml::ConstNodeRef root = tree.crootref();
	for (c4::yml::ConstNodeRef entityNode : root.children())
	{
		std::ostringstream keyStream;
		keyStream << entityNode.key();
		Entity* entity = scene->createEntity(keyStream.str());
		EntityParser::deserialize(scene, entityNode, entity);
	}
}

} // namespace sre
