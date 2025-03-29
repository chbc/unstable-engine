#include "Material.h"
#include "ColorMaterialComponent.h"
#include "LitMaterialComponent.h"
#include "BoolEditorProperty.h"
#include "Vec2EditorProperty.h"
#include "FileUtils.h"

namespace sre
{

Material::Material(std::string arg_filePath) : castShadow(false), uvOffset(glm::vec2(0.0f)), uvTiling(glm::vec2(1.0f))
{
    this->addEditorProperty(new BoolEditorProperty{ "Cast Shadow", &this->castShadow });
    this->addEditorProperty(new Vec2EditorProperty{ "UV Offset", &this->uvOffset });
    this->addEditorProperty(new Vec2EditorProperty{ "UV Tiling", &this->uvTiling });
    this->addComponent<ColorMaterialComponent>();
    this->filePath = FileUtils::getContentRelativePath(arg_filePath);
}

AMaterialComponent* Material::addComponent(const char* className)
{
    AMaterialComponent* newComponent{ nullptr };

    newComponent = AMaterialComponent::Create(className, this);
    uint16_t id = newComponent->getId();
    assert(this->componentsMap.count(id) == 0);

    this->componentsMap.emplace(id, newComponent);
    this->componentsBitset[id] = true;

    return newComponent;
}

void Material::setCastShadow(bool value)
{
	this->castShadow = value;
}

void Material::setReceivesLight(bool value)
{
    bool hasLit = this->hasComponent<LitMaterialComponent>();
    if (value && !hasLit)
        this->addComponent<LitMaterialComponent>();
    else if (!value && hasLit)
        this->removeComponent<LitMaterialComponent>();
}

bool Material::getReceivesLight()
{
    return this->hasComponent<LitMaterialComponent>();
}

void Material::setUVOffset(glm::vec2 uvOffset)
{
    this->uvOffset = uvOffset;
}

void Material::setUVTiling(glm::vec2 uvTiling)
{
    this->uvTiling = uvTiling;
}

glm::vec2 Material::getUVOffset()
{
    return uvOffset;
}

glm::vec2 Material::getUVTiling()
{
    return uvTiling;
}

void Material::addEditorProperty(AEditorProperty* editorProperty)
{
    editorProperty->onValueSerializedCallback = std::bind(&Material::onPropertySerialized, this);
    editorProperty->onValueDeserializedCallback = std::bind(&Material::onPropertyDeserialized, this);
    editorProperty->onValueChangedCallback = std::bind(&Material::onPropertyChanged, this);
    this->editorProperties.emplace_back(editorProperty);
}

} // namespace
