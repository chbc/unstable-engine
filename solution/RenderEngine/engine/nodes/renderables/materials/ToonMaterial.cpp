#include "ToonMaterial.h"

ToonMaterial::ToonMaterial(const std::string &fileName, int layersCount) : DiffuseMaterial(fileName)
{
	this->loadShader(shaderConsts::TOON_V, shaderConsts::TOON_F);
	this->loadTexture(fileName);

	this->layersCount = layersCount;
}
