#include "EntityLoader.h"
#include "FileUtils.h"
#include "Entity.h"
#include "AScene.h"
#include "EntityParser.h"

#include <c4/yml/std/string.hpp>

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

Entity* EntityLoader::load(const char* filePath, std::string name, AScene* scene)
{
	std::string fileContent;
	FileUtils::loadContentFile(filePath, fileContent);
	c4::substr bufferSubstr = RYMLLib::toC4Substr(fileContent);

	c4::yml::Tree tree = c4::yml::parse_in_place(bufferSubstr);
	c4::yml::ConstNodeRef root = tree.crootref();
	char entityName[] = "Entity";
	c4::csubstr className = entityName;
	if (root.has_child("Class"))
	{
		root["Class"] >> className;
	}

	std::string classNameStr(className.str, className.len);
	Entity* result = Entity::Create(name, classNameStr);
	result->filePath = FileUtils::getContentRelativePath(filePath);
	EntityParser::deserialize(root, scene, result);
	result->setStored(true);

	return result;
}

} // namespace sre
