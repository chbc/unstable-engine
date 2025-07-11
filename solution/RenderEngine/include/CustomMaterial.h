#pragma once

#include "ABaseMaterial.h"

namespace sre
{

class CustomMaterial : public ABaseMaterial
{
private:
	std::string shaderFilePath;

public:
	CustomMaterial(const std::string& arg_filePath, const std::string& arg_shaderFilePath);
	const std::string& getShaderFilePath();
};

} // namespace
