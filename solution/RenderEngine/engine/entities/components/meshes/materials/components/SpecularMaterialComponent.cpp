#include "SpecularMaterialComponent.h"

namespace sre
{
SpecularMaterialComponent::SpecularMaterialComponent(Material *material, const std::string &fileName)
	: NormalMaterialComponent(material, fileName)
{ }

} // namespace
