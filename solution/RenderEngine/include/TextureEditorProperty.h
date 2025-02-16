#pragma once

#include "AEditorProperty.h"
#include "ETextureMap.h"

namespace sre
{

class Texture;

class TextureEditorProperty : public AEditorProperty
{

DECLARE_PROPERTY()

private:
	ETextureMap::Type textureMapType;
	Texture** texture;
	void* id;

public:
	TextureEditorProperty(const char* title, Texture** arg_texture, ETextureMap::Type arg_textureMapType);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
