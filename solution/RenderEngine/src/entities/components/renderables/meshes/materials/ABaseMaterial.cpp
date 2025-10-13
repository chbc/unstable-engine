#include "ABaseMaterial.h"
#include "FileUtils.h"
#include "StringEditorProperty.h"
#include "AMaterialComponent.h"
#include <cassert>

namespace sre
{

ABaseMaterial::ABaseMaterial(const std::string& arg_filePath, EMaterialType arg_type)
    : type(arg_type)
{
	this->filePath = FileUtils::getContentRelativePath(arg_filePath);
    std::string typeString = (this->type == EMaterialType::STANDARD) ? "Standard" : "Custom";
    
    this->addEditorProperty(new StringEditorProperty{ "Material Type", typeString });
}

AMaterialComponent* ABaseMaterial::addComponent(const char* className)
{
    AMaterialComponent* newComponent{ nullptr };

    newComponent = AMaterialComponent::Create(className, this);
    uint16_t id = newComponent->getId();
    assert(this->componentsMap.count(id) == 0);

    this->componentsMap.emplace(id, newComponent);
    this->componentsBitset[id] = true;

    return newComponent;
}

bool ABaseMaterial::isStandard()
{
    return (this->type == EMaterialType::STANDARD);
}

const std::string& ABaseMaterial::getFilePath() const
{
	return this->filePath;
}

void ABaseMaterial::addEditorProperty(AEditorProperty* editorProperty)
{
    editorProperty->onValueSerializedCallback = std::bind(&ABaseMaterial::onPropertySerialized, this);
    editorProperty->onValueDeserializedCallback = std::bind(&ABaseMaterial::onPropertyDeserialized, this);
    editorProperty->onValueChangedCallback = std::bind(&ABaseMaterial::onPropertyChanged, this);
    this->editorProperties.emplace_back(editorProperty);
}

} // namespace
