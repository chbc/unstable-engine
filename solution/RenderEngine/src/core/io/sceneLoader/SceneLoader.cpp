#include "SceneLoader.h"
#include "FileUtils.h"
#include "Scene.h"
#include "EntityParser.h"

namespace sre
{

void SceneLoader::save(Scene* scene)
{
	c4::yml::Tree tree;
	c4::yml::NodeRef root = tree.rootref();

	root |= ryml::MAP;
	for (const auto& entityItem : scene->entities)
	{
		c4::yml::NodeRef entityNode = root[entityItem.first.c_str()];
		EntityParser::serialize(entityNode, entityItem.second.get());
	}

	std::string content = c4::yml::emitrs_yaml<std::string>(tree);
	FileUtils::saveFile("../../scenes/test.scene", content);
}

void SceneLoader::load(Scene* scene, const char* sceneName)
{
	std::string fileContent;
	FileUtils::loadFile(sceneName, fileContent);

	c4::yml::Tree tree = c4::yml::parse_in_place(c4::to_substr(fileContent));

	c4::yml::ConstNodeRef root = tree.crootref();
	for (c4::yml::ConstNodeRef entityNode : root.children())
	{
		Entity* entity = scene->createEntity(entityNode.key().str);
		EntityParser::deserialize(entityNode, entity);
	}
}

} // namespace sre