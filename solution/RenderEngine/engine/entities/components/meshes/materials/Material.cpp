#include "Material.h"
#include <engine/systems/graphics/RenderManager.h>
#include "components/ColorMaterialComponent.h"

namespace sre
{

Material::Material()
{
	this->shaderProgram = 0;
	// ### this->addComponent<ColorMaterialComponent>();
}

void Material::loadShader(const std::string &vertexFile, const std::string &fragmentFile)
{
	// ### this->shaderProgram = this->renderManager->loadShader(vertexFile, fragmentFile);
}

} // namespace
