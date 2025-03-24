#include "EntityLoader.h"
#include "FileUtils.h"
#include "Entity.h"
#include "AScene.h"
#include "EntityParser.h"

namespace sre
{

void EntityLoader::save(Entity* entity, const char* filePath)
{
	if (entity->isStored())
	{
		return;
	}

	entity->setStored(false);

	c4::yml::Tree tree;
	c4::yml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	std::string className{ entity->getClassName() };
	if (className != "Entity")
	{
		root["Class"] << className;
	}
	EntityParser::serialize(root, entity);

	std::string content = c4::yml::emitrs_yaml<std::string>(tree);
	FileUtils::saveContentFile(filePath, content);

	entity->setStored(true);
}

Entity* EntityLoader::load(const char* filePath, std::string name)
{
	std::string fileContent;
	FileUtils::loadContentFile(filePath, fileContent);

	c4::yml::Tree tree = c4::yml::parse_in_place(c4::to_substr(fileContent));
	c4::yml::ConstNodeRef root = tree.crootref();
	std::string className{ "Entity" };
	if (root.has_child("Class"))
	{
		root["Class"] >> className;
	}

	Entity* result = Entity::Create(name, className.c_str());
	result->filePath = filePath;
	EntityParser::deserialize(root, result);
	result->setStored(true);

	return result;
}

} // namespace sre
