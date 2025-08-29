#include "TextureEditorProperty.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "Texture.h"

#include "rapidyaml.hpp"
#include "imgui.h"

namespace sre
{

TextureEditorProperty::TextureEditorProperty(const char* title, Texture** arg_texture, ETextureMap::Type arg_textureMapType)
	: AEditorProperty(title), texture(arg_texture), textureMapType(arg_textureMapType)
{ }

void TextureEditorProperty::setTextureId(void* arg_id)
{
	this->id = reinterpret_cast<uint64_t>(arg_id);
}

void TextureEditorProperty::onDraw()
{
	ImGui::Image(this->id, ImVec2{ 64.0f, 64.0f });
	this->handleTextureDragAndDrop();
}

void TextureEditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode |= ryml::MAP;
	propertyNode["TextureMapType"] << static_cast<int>(this->textureMapType);
	propertyNode["FilePath"] << (*this->texture)->getFilePath();
}

void TextureEditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	std::string fileName;
	int mapType = 0;
	propertyNode["TextureMapType"] >> mapType;
	propertyNode["FilePath"] >> fileName;

	this->textureMapType = static_cast<ETextureMap::Type>(mapType);

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	*this->texture = assetsManager->loadTexture(fileName.c_str(), this->textureMapType);
	this->id = static_cast<uint64_t>((*this->texture)->getId());
}

void TextureEditorProperty::copy(AEditorProperty* destination)
{
	TextureEditorProperty* derivedProperty = static_cast<TextureEditorProperty*>(destination);
	derivedProperty->textureMapType = this->textureMapType;
	*derivedProperty->texture = *this->texture;
	derivedProperty->id = this->id;
}

void TextureEditorProperty::handleTextureDragAndDrop()
{
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE"))
		{
			const char* filePath = static_cast<const char*>(payload->Data);
			if (filePath != nullptr)
			{
				AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
				*this->texture = assetsManager->loadTexture(filePath, this->textureMapType);
				this->id = static_cast<uint64_t>((*this->texture)->getId());

				this->onPropertyChanged();
			}
		}
		ImGui::EndDragDropTarget();
	}
}

} // namespace
