#include "CustomMaterialComponent.h"
#include "TextureEditorProperty.h"
#include "Texture.h"

namespace sre
{
IMPLEMENT_MATERIAL_COMPONENT(CustomMaterialComponent, CUSTOM_MATERIAL)

CustomMaterialComponent::CustomMaterialComponent(ABaseMaterial *material)
    : ABaseTextureMaterialComponent(material)
{ }

AEditorProperty* CustomMaterialComponent::addTextureProperty(const std::string& uniformVariable)
{
    this->texturesMap[uniformVariable] = nullptr;

    AEditorProperty* result = new TextureEditorProperty{ uniformVariable, &this->texturesMap[uniformVariable], ETextureMap::CUSTOM };
    this->addEditorProperty(result);

    return result;
}

TexturesMap& CustomMaterialComponent::getTexturesMap()
{
    return this->texturesMap;
}

} // namespace
