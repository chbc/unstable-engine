#include "Material.h"
#include <engine/systems/graphics/RenderManager.h>
#include <string.h>

using graphics::RenderManager;

Material::Material()
{
	this->renderManager = RenderManager::getInstance();
	this->shaderProgram = 0;

	float amb[4] = {0.3f, 0.3f, 0.3f, 1.0f};
	this->ambient = new float[4];
	memcpy(this->ambient, amb, 4 * sizeof(float));

	float dif[4] = {0.7f, 0.7f, 0.7f, 1.0f};
	this->diffuse = new float[4];
	memcpy(this->diffuse, dif, 4 * sizeof(float));

	float spe[4] = {0.9f, 0.9f, 0.9f, 1.0f};
	this->specular = new float[4];
	memcpy(this->specular, spe, 4 * sizeof(float));

	this->shininess = 8;
}

Material::~Material()
{
	delete [] this->ambient;
	delete [] this->diffuse;
	delete [] this->specular;
}

void Material::loadShader(const std::string &vertexFile, const std::string &fragmentFile)
{
	this->shaderProgram = this->renderManager->loadShader(vertexFile, fragmentFile);
}

void Material::setAmbient(float *ambient)
{
	this->ambient = ambient;
}

void Material::setDiffuse(float *diffuse)
{
	this->diffuse = diffuse;
}

void Material::setSpecular(float *specular)
{
	this->specular = specular;
}
