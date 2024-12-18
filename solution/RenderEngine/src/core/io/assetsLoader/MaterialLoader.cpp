#include "MaterialLoader.h"
#include "FileUtils.h"
#include "Material.h"
#include "AMaterialComponent.h"
#include "ColorMaterialComponent.h"
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

	root |= ryml::MAP;
	for (const SPTR<AEditorProperty>& property : material->editorProperties)
	{
		c4::yml::NodeRef& propertyNode = root[property->title.c_str()];
		property->serialize(propertyNode);
	}

	c4::yml::NodeRef ComponentsNode = root["Components"];
	ComponentsNode |= ryml::MAP;
	for (const auto& componentItem : material->componentsMap)
	{
		AMaterialComponent* component = componentItem.second.get();
		c4::yml::NodeRef itemtNode = ComponentsNode[component->getClassName()];
		serializeComponent(itemtNode, component);
	}

	std::string filePath = BASE_FOLDER + name;
	std::string content = c4::yml::emitrs_yaml<std::string>(tree);
	FileUtils::saveFile(filePath, content);
}

Material* sre::MaterialLoader::load(const char* fileName)
{

	std::string fileContent;
	std::string filePath = BASE_FOLDER + fileName;

	FileUtils::loadFile(filePath, fileContent);
	c4::yml::Tree tree = c4::yml::parse_in_place(c4::to_substr(fileContent));
	c4::yml::ConstNodeRef root = tree.crootref();

	Material* result = new Material;
	for (auto& property : result->editorProperties)
	{
		c4::yml::ConstNodeRef& propertyNode = root[property->title.c_str()];
		property->deserialize(propertyNode);
	}

	c4::yml::ConstNodeRef& componentsNode = root["Components"];
	for (c4::yml::ConstNodeRef componentNode : componentsNode.children())
	{
		this->deserializeComponent(componentNode, result);
	}

	return result;
}

void MaterialLoader::serializeComponent(c4::yml::NodeRef& componentNode, AMaterialComponent* component)
{
	componentNode |= ryml::MAP;
	for (const SPTR<AEditorProperty>& property : component->editorProperties)
	{
		c4::yml::NodeRef& propertyNode = componentNode[property->title.c_str()];
		property->serialize(propertyNode);
	}
}

void MaterialLoader::deserializeComponent(c4::yml::ConstNodeRef& componentNode, Material* material)
{
	std::ostringstream keyStream;
	keyStream << componentNode.key();
	std::string type = keyStream.str();

	AMaterialComponent* component = nullptr;
	if (type == "ColorMaterialComponent")
	{
		component = material->getComponent<ColorMaterialComponent>();
	}
	else
	{
		component = material->addComponent(type.c_str());
	}

	for (const SPTR<AEditorProperty>& property : component->editorProperties)
	{
		c4::yml::ConstNodeRef& propertyNode = componentNode[property->title.c_str()];
		property->deserialize(propertyNode);
	}
}

} // namespace
