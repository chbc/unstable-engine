#include "MaterialLoader.h"
#include "FileUtils.h"
#include <rapidyaml/rapidyaml.hpp>

// XXX MOVER PRA UM ARQUIVO APROPRIADO
#ifdef __ANDROID__
	const std::string BASE_FOLDER = "media/es/";
#else
	const std::string BASE_FOLDER = "../../media/";
#endif

namespace sre
{

void MaterialLoader::save(Material* material, const char* name)
{
	c4::yml::Tree tree;
	c4::yml::NodeRef root = tree.rootref();

	/*
	root |= ryml::MAP;
	for (const auto& entityItem : scene->entities)
	{
		c4::yml::NodeRef entityNode = root[entityItem.first.c_str()];
		EntityParser::serialize(entityNode, entityItem.second.get());
	}

	std::string filePath = BASE_FOLDER + sceneName + std::string{ ".scene" };
	std::string content = c4::yml::emitrs_yaml<std::string>(tree);
	FileUtils::saveFile(filePath, content);
	*/
}

Material* sre::MaterialLoader::load(const char* fileName)
{
	Material* result{ nullptr };

	/*
	std::string fileContent;
	std::string filePath = BASE_FOLDER + fileName;
	*/

	return result;
}

} // namespace
