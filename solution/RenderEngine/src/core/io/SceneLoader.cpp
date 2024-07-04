#include "SceneLoader.h"
#include "FileUtils.h"
#include "Scene.h"

#include <sstream>

#include <iostream>

#define RYML_SINGLE_HDR_DEFINE_NOW
#include <rapidyaml/rapidyaml.hpp>

namespace sre
{

void deserializeEntity(const c4::yml::NodeRef& entityNode, Entity* entity);

void SceneLoader::load(Scene* scene)
{
	std::string fileContent;
	FileUtils::loadFile("../../scenes/default.scene", fileContent);

	c4::yml::Tree tree = c4::yml::parse_in_place(c4::to_substr(fileContent));

	c4::yml::NodeRef entityNodes = tree["entities"];
	if (entityNodes.has_children())
	{
		for (const c4::yml::NodeRef& item : entityNodes)
		{
			std::stringstream name;
			name << item["name"].val();
			Entity* entity = scene->createEntity(name.str());

			std::cout << item["name"] << std::endl;
			deserializeEntity(item, entity);
			std::cout << std::endl;
		}
	}
}

void deserializeEntity(const c4::yml::NodeRef& entityNode, Entity* entity)
{
	c4::yml::ConstNodeRef components = entityNode["components"];
	if (components.has_children())
	{
		for (c4::yml::ConstNodeRef& item : components.children())
		{
			std::cout << item["name"].key() << ": " << item["name"].val() << std::endl;

			// COMEÇAR PELA SERIALIZAÇÃO
			// REVER ESTRUTURA DO arquivo YAML (talvez não precise do "name")
			// CRIAR UM WRAPPER PARA ENCAPSULAR O RAPIDYAML
			// INCLUIR TODOS OS COMPONENTES AQUI
			// PROCURAR O NÓ POR CADA COMPONENTE E CRIAR USANDO entity
			// CHAMAR deserialize
			// A PARTIR DO COMPONENTE, OBTER TODOS OS VALORES USANDO O WRAPPER
		}
	}
}

void SceneLoader::save(Scene* scene)
{

}

} // namespace sre
