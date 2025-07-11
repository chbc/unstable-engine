#include "CustomMaterial.h"
#include "StringEditorProperty.h"

namespace sre
{

CustomMaterial::CustomMaterial(const std::string& arg_filePath, const std::string& arg_shaderFilePath)
	: ABaseMaterial(arg_filePath, EMaterialType::CUSTOM), shaderFilePath(arg_shaderFilePath)
{
	this->addEditorProperty(new StringEditorProperty{ "Shader File", this->shaderFilePath });
}

const std::string& CustomMaterial::getShaderFilePath()
{
	return this->shaderFilePath;
}

} // namespace
