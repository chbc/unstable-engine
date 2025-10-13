#pragma once

#include "ABaseMaterial.h"
#include "EShaderComponent.h"

#include <unordered_map>

namespace sre
{

class Texture;

using ShaderPathsMap = std::unordered_map<EShaderComponent::Type, std::string>;

class CustomMaterial : public ABaseMaterial
{
private:
	ShaderPathsMap shaderPaths;

public:
	CustomMaterial(const std::string& arg_filePath, const ShaderPathsMap& arg_shaderPaths);
	const ShaderPathsMap& getShaderFilePaths() const;
};

} // namespace
