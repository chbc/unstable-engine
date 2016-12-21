#include "Material.h"
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

Material::Material()
{
	this->shaderProgram = 0;
	ColorMaterialComponent *component = this->addComponent<ColorMaterialComponent>();
	component->init();
}

void Material::loadShader(const std::string &vertexFile, const std::string &fragmentFile)
{
	this->shaderProgram = RenderManager::getInstance()->loadShader(vertexFile, fragmentFile);
}

} // namespace
