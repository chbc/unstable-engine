#include "FontEditorProperty.h"
#include "FontAtlas.h"
#include "MeshData.h"
#include "FileUtils.h"
#include "SingletonsManager.h"
#include "AtlasManager.h"

#include "GuiWrapper.h"
#include "rapidyaml/rapidyaml.hpp"
#include "glm/vec2.hpp"

namespace sre
{

FontEditorProperty::FontEditorProperty(const char* title, FontAtlas** arg_fontAtlas)
	: AEditorProperty(title), fontAtlas(arg_fontAtlas)
{ }

void FontEditorProperty::onDraw()
{
	if (this->filePath.empty())
	{
		this->filePath = (*this->fontAtlas)->getFilePath();
	}

	const AtlasItem* item = (*this->fontAtlas)->getItem('A');
	Texture* texture = (*this->fontAtlas)->getTexture();

	ImVec2 uv1{ item->uv.topLeft.x, item->uv.topLeft.y };
	ImVec2 uv2{ uv1.x + item->uv.size.x, uv1.y + item->uv.size.y };
	ImGui::Image(texture->getId(), ImVec2{16.0f, 16.0f}, uv1, uv2);

	ImGui::Text(this->filePath.c_str());
}

void FontEditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	propertyNode |= ryml::MAP;
	propertyNode["FilePath"] << (*this->fontAtlas)->getFilePath();
}

void FontEditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	propertyNode["FilePath"] >> this->filePath;

	SingletonsManager* singletonsManager = SingletonsManager::getInstance();
	*this->fontAtlas = singletonsManager->get<AtlasManager>()->getFont(filePath);
}

void FontEditorProperty::copy(AEditorProperty* destination)
{
	FontEditorProperty* derivedProperty = static_cast<FontEditorProperty*>(destination);
	*derivedProperty->fontAtlas = *this->fontAtlas;
}

} // namespace
