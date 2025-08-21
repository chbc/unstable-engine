#pragma once

#include "ModelImportData.h"

namespace c4
{
	namespace yml
	{
		class NodeRef;
	}
}

namespace sre
{

class MaterialSaver
{
public:
	void save(MaterialImportData& modelData, const std::string& filePath);

private:
	void saveComponents(const MaterialImportData& materialData, c4::yml::NodeRef& componentsNode, const std::string& filePath);
	void setupMissingMaterialTextures(const MaterialImportData& material, c4::yml::NodeRef& pbrNode);
};

} // namespace
