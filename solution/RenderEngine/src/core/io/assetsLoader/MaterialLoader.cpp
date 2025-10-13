#include "MaterialLoader.h"
#include "FileUtils.h"
#include "Material.h"
#include "CustomMaterial.h"
#include "AMaterialComponent.h"
#include "ColorMaterialComponent.h"
#include "CustomMaterialComponent.h"

namespace sre
{

void MaterialLoader::save(ABaseMaterial* material, const std::string& filePath)
{
	c4::yml::Tree tree;
	c4::yml::NodeRef root = tree.rootref();

	root |= ryml::MAP;
	for (const SPTR<AEditorProperty>& property : material->editorProperties)
	{
		c4::yml::NodeRef& propertyNode = root[property->title.c_str()];
		property->serialize(propertyNode);
	}

	if (material->isStandard())
	{
		Material* standardMaterial = static_cast<Material*>(material);
		c4::yml::NodeRef componentsNode = root["Components"];
		this->saveComponents(standardMaterial, componentsNode);
	}

	std::string content = c4::yml::emitrs_yaml<std::string>(tree);
	FileUtils::saveContentFile(filePath, content);
}

ABaseMaterial* sre::MaterialLoader::load(const std::string& filePath)
{
	std::string fileContent;
	FileUtils::loadContentFile(filePath, fileContent);
	c4::yml::Tree tree = c4::yml::parse_in_place(c4::to_substr(fileContent));
	c4::yml::ConstNodeRef root = tree.crootref();

	std::string type;
	root["Material Type"] >> type;

	ABaseMaterial* result = nullptr;
	if (type == "Standard")
	{
		result = this->loadStandardMaterial(filePath, root);
	}
	else
	{
		result = this->loadCustomMaterial(filePath, root);
	}

	return result;
}

void MaterialLoader::saveComponents(Material* material, c4::yml::NodeRef& componentsNode)
{
	componentsNode |= ryml::MAP;
	for (const auto& componentItem : material->componentsMap)
	{
		AMaterialComponent* component = componentItem.second.get();
		c4::yml::NodeRef itemtNode = componentsNode[component->getClassName()];
		serializeComponent(itemtNode, component);
	}
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

ABaseMaterial* MaterialLoader::loadStandardMaterial(const std::string& filePath, c4::yml::ConstNodeRef& root)
{
	Material* result = new Material{ filePath };
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

ABaseMaterial* MaterialLoader::loadCustomMaterial(const std::string& filePath, c4::yml::ConstNodeRef& root)
{
	// Shaders
	c4::yml::ConstNodeRef& shadersNode = root["Shaders"];
	ShaderPathsMap shaderPaths;
	for (c4::yml::ConstNodeRef itemNode : shadersNode.children())
	{
		std::ostringstream keyStream;
		keyStream << itemNode.key();
		std::string key = keyStream.str();
		std::string valuePath;
		itemNode >> valuePath;
		if (key == "Vertex")
		{
			shaderPaths[EShaderComponent::VERTEX] = valuePath;
		}
		else if (key == "Fragment")
		{
			shaderPaths[EShaderComponent::FRAGMENT] = valuePath;
		}
		else if (key == "Geometry")
		{
			shaderPaths[EShaderComponent::GEOMETRY] = valuePath;
		}
	}

	/*
	// Textures
	c4::yml::ConstNodeRef &texturesNode = root["Textures"];
	TexturesMap texturesMap;
	for (c4::yml::ConstNodeRef itemNode : shadersNode.children())
	{
		std::ostringstream keyStream;
		keyStream << itemNode.key();
		std::string key = keyStream.str();
		std::string valuePath;
		itemNode >> valuePath;
	
		texturesMap[key] = valuePath;
	}
	*/

	CustomMaterial* result = new CustomMaterial{ filePath, shaderPaths };
	if (root.has_child("Components"))
	{
		c4::yml::ConstNodeRef& componentsNode = root["Components"];
		for (c4::yml::ConstNodeRef componentNode : componentsNode.children())
		{
			this->deserializeCustomComponent(componentNode, result);
		}
	}

	return result;
}

void MaterialLoader::deserializeComponent(c4::yml::ConstNodeRef& componentNode, ABaseMaterial* material)
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

void MaterialLoader::deserializeCustomComponent(c4::yml::ConstNodeRef& componentNode, ABaseMaterial* material)
{
	std::ostringstream keyStream;
	keyStream << componentNode.key();
	std::string type = keyStream.str();

	CustomMaterialComponent* component = static_cast<CustomMaterialComponent*>(material->addComponent(type.c_str()));
	for (c4::yml::ConstNodeRef& propertyNode : componentNode.children())
	{
		std::ostringstream uniformStream;
		uniformStream << propertyNode.key();

		AEditorProperty* editorProperty = component->addTextureProperty(uniformStream.str());
		editorProperty->deserialize(propertyNode);
	}
}

} // namespace
