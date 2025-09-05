#include "MaterialSaver.h"
#include "FileUtils.h"

#define RYML_SINGLE_HDR_DEFINE_NOW
#include "rapidyaml/rapidyaml.hpp"

namespace sre
{

void MaterialSaver::save(MaterialImportData& modelData, const std::string& filePath)
{
	c4::yml::Tree tree;
	c4::yml::NodeRef root = tree.rootref();

	root |= ryml::MAP;

	root["Material Type"] << "Standard";
	root["Cast Shadow"] << 0;

	c4::yml::NodeRef propertyNode = root["UV Offset"];
	propertyNode |= c4::yml::SEQ | c4::yml::CONTAINER_STYLE;
	propertyNode.append_child() << 0;
	propertyNode.append_child() << 0;

	propertyNode = root["UV Tiling"];
	propertyNode |= c4::yml::SEQ | c4::yml::CONTAINER_STYLE;
	propertyNode.append_child() << 1;
	propertyNode.append_child() << 1;

	c4::yml::NodeRef componentsNode = root["Components"];
	this->saveComponents(modelData, componentsNode, filePath);

	std::string content = c4::yml::emitrs_yaml<std::string>(tree);
	FileUtils::saveContentFile(filePath, content);
}

void MaterialSaver::saveComponents(const MaterialImportData& materialData, c4::yml::NodeRef& componentsNode, const std::string& filePath)
{
	componentsNode |= ryml::MAP;
	c4::yml::NodeRef componentNode = componentsNode["LitMaterialComponent"];

	componentNode |= ryml::MAP;
	componentNode["Shininess"] << 1;

	c4::yml::NodeRef pbrNode = componentsNode["PBRMaterialComponent"];

	for (const auto& item : materialData.texturePaths)
	{
		const char* typeString = MaterialImportData::getTypeString(item.first);
		pbrNode |= ryml::MAP;
		c4::yml::NodeRef propertyNode = pbrNode[typeString];

		propertyNode |= ryml::MAP;
		propertyNode["TextureMapType"] << static_cast<int>(item.first);
		
		std::string texturePath = FileUtils::getBasePath(filePath) + "\\" + item.second;
		texturePath = FileUtils::getContentRelativePath(texturePath);
		propertyNode["FilePath"] << texturePath;

		if (item.first == ETextureMap::NORMAL)
		{
			propertyNode["FlipGreenChannel"] << 0;
		}
	}

	this->setupMissingMaterialTextures(materialData, pbrNode);
}

void MaterialSaver::setupMissingMaterialTextures(const MaterialImportData& material, c4::yml::NodeRef& pbrNode)
{
	std::unordered_map<ETextureMap::Type, std::string> defaultTextures =
	{
		{ ETextureMap::DIFFUSE, "engine/media/textures/pbr_default_albedo.png" },
		{ ETextureMap::NORMAL, "engine/media/textures/pbr_default_normal.png" },
		{ ETextureMap::ROUGHNESS, "engine/media/textures/pbr_default_occlusion_roughness_metallic.png" },
		{ ETextureMap::METALLIC, "engine/media/textures/pbr_default_occlusion_roughness_metallic.png" },
		{ ETextureMap::AMBIENT_OCCLUSION, "engine/media/textures/pbr_default_occlusion_roughness_metallic.png" }
	};

	for (const auto& item : defaultTextures)
	{
		if (material.texturePaths.count(item.first) < 1)
		{
			const char* typeString = MaterialImportData::getTypeString(item.first);
			pbrNode |= ryml::MAP;
			c4::yml::NodeRef propertyNode = pbrNode[typeString];

			propertyNode |= ryml::MAP;
			propertyNode["TextureMapType"] << static_cast<int>(item.first);
			propertyNode["FilePath"] << item.second;
		}
	}
}

} // namespace
