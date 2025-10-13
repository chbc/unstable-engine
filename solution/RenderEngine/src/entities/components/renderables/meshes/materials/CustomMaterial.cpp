#include "CustomMaterial.h"
#include "StringEditorProperty.h"
#include "TextureEditorProperty.h"

namespace sre
{

CustomMaterial::CustomMaterial(const std::string& arg_filePath, const ShaderPathsMap& arg_shaderPaths)
	: ABaseMaterial(arg_filePath, EMaterialType::CUSTOM), shaderPaths(arg_shaderPaths)
{
	for (const auto& item : this->shaderPaths)
	{
		std::string propertyTitle = getShaderComponentString(item.first);
		this->addEditorProperty(new StringEditorProperty{ propertyTitle, item.second });
	}
}

const ShaderPathsMap& CustomMaterial::getShaderFilePaths() const
{
	return this->shaderPaths;
}

} // namespace
