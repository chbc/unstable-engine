#include "EntityLoader.h"
#include "FileUtils.h"
#include "Entity.h"
#include "AScene.h"
#include "EntityParser.h"
#include "Paths.h"

namespace sre
{

void EntityLoader::save(Entity* entity, const char* fileName)
{
	c4::yml::Tree tree;
	c4::yml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	std::string className{ entity->getClassName() };
	if (className != "Entity")
	{
		root["Class"] << className;
	}
	EntityParser::serialize(root, entity);

	std::string filePath;
	Paths().buildMediaFilePath(fileName, filePath, false);
	std::string content = c4::yml::emitrs_yaml<std::string>(tree);
	FileUtils::saveFile(filePath, content);
}

Entity* EntityLoader::load(const char* fileName, std::string name)
{
	std::string fileContent;
	std::string filePath;
	Paths().buildMediaFilePath(fileName, filePath);
	FileUtils::loadFile(filePath, fileContent);

	c4::yml::Tree tree = c4::yml::parse_in_place(c4::to_substr(fileContent));
	c4::yml::ConstNodeRef root = tree.crootref();
	std::string className{ "Entity" };
	if (root.has_child("Class"))
	{
		root["Class"] >> className;
	}

	Entity* result = Entity::Create(name, className.c_str());
	result->fileName = fileName;
	EntityParser::deserialize(root, result);

	return result;
}

} // namespace sre
