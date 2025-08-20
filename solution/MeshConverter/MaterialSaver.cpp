#include "MaterialSaver.h"
#include "FileUtils.h"

#define RYML_SINGLE_HDR_DEFINE_NOW
#include "rapidyaml/rapidyaml.hpp"

namespace sre
{

void MaterialSaver::save(const MaterialImportData& modelData, const std::string& filePath)
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
	this->saveComponents(componentsNode, modelData, filePath);

	std::string content = c4::yml::emitrs_yaml<std::string>(tree);
	FileUtils::saveContentFile(filePath, content);
}

void MaterialSaver::saveComponents(c4::yml::NodeRef& componentsNode, const MaterialImportData& materialData, const std::string& filePath)
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
	}
}

} // namespace
