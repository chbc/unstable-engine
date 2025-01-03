#include "TextureEditorProperty.h"
#include "SingletonsManager.h"
#include "AssetsManager.h"
#include "Paths.h"
#include "Texture.h"

#include <rapidyaml/rapidyaml.hpp>
#include "imgui/imgui.h"

namespace sre
{

TextureEditorProperty::TextureEditorProperty(const char* title, Texture** arg_texture, ETextureMap::Type arg_textureMapType)
	: AEditorProperty(title), texture(arg_texture), textureMapType(arg_textureMapType), id(nullptr)
{ }

void TextureEditorProperty::draw()
{
	ImGui::PushID(this->title.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 100.0f);
	ImGui::Text(this->title.c_str());
	ImGui::NextColumn();
	ImGui::SetColumnWidth(0, 100.0f);

	ImGui::Image(this->id, ImVec2{ 64.0f, 64.0f});

	ImGui::Columns(1);

	ImGui::PopID();
}

void TextureEditorProperty::serialize(c4::yml::NodeRef& propertyNode)
{
}

void TextureEditorProperty::deserialize(c4::yml::ConstNodeRef& propertyNode)
{
	std::string fileName;
	int mapType = 0;
	propertyNode["TextureMapType"] >> mapType;
	propertyNode["File"] >> fileName;

	this->textureMapType = static_cast<ETextureMap::Type>(mapType);

	AssetsManager* assetsManager = SingletonsManager::getInstance()->get<AssetsManager>();
	std::string filePath;
	Paths().buildMediaFilePath(EContentType::ENGINE, fileName.c_str(), filePath);
	*this->texture = assetsManager->loadTexture(filePath.c_str(), this->textureMapType);
	this->id = reinterpret_cast<void*>((*this->texture)->getId());
}

} // namespace
