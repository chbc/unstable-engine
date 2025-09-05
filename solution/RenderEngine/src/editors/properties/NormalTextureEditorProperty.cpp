#include "NormalTextureEditorProperty.h"
#include "Texture.h"

#include "imgui.h"
#include "rapidyaml.hpp"

namespace sre
{

NormalTextureEditorProperty::NormalTextureEditorProperty(const char* title, Texture** arg_texture)
	: TextureEditorProperty(title, arg_texture, ETextureMap::NORMAL)
{
}

void NormalTextureEditorProperty::onDraw()
{
	if (ImGui::Checkbox("Flip Green Channel", &this->flipGreenChannel))
	{
		(*this->texture)->setFlipGreenChannel(this->flipGreenChannel);
	}
	TextureEditorProperty::onDraw();
}

void NormalTextureEditorProperty::onSerialize(c4::yml::NodeRef& propertyNode)
{
	TextureEditorProperty::onSerialize(propertyNode);
	propertyNode["FlipGreenChannel"] << this->flipGreenChannel;
}

void NormalTextureEditorProperty::onDeserialize(c4::yml::ConstNodeRef& propertyNode)
{
	TextureEditorProperty::onDeserialize(propertyNode);
	propertyNode["FlipGreenChannel"] >> this->flipGreenChannel;
	(*this->texture)->setFlipGreenChannel(this->flipGreenChannel);
}

void NormalTextureEditorProperty::copy(AEditorProperty* destination)
{
	TextureEditorProperty::copy(destination);
	NormalTextureEditorProperty* derivedProperty = static_cast<NormalTextureEditorProperty*>(destination);
	derivedProperty->flipGreenChannel = this->flipGreenChannel;
}

}  // namespace
