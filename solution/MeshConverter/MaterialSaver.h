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
	void save(const MaterialImportData& modelData, const std::string& filePath);

private:
	void saveComponents(c4::yml::NodeRef& componentsNode, const MaterialImportData& materialData, const std::string& filePath);
};

} // namespace
