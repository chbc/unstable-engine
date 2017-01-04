#include "Material.h"
#include <engine/systems/graphics/RenderManager.h>

namespace sre
{

Material::Material()
{
	ColorMaterialComponent *component = this->addComponent<ColorMaterialComponent>();
	component->init();
}

} // namespace
