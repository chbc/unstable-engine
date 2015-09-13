#include "SpecularMaterial.h"

SpecularMaterial::SpecularMaterial(const std::string &fileName, float shininess) : DiffuseMaterial(fileName)
{
	this->loadShader(shaderConsts::SPECULAR_V, shaderConsts::SPECULAR_F);
	this->loadTexture(fileName);

	this->shininess = shininess;
}

void SpecularMaterial::setShininess(float shininess)
{
	this->shininess = shininess;
}
