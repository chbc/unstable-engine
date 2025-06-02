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
	ETextureMap::Type textureMapType{ ETextureMap::EMPTY };
	Texture** texture{ nullptr };
	uint64_t id{ 0 };

public:
	TextureEditorProperty(const char* title, Texture** arg_texture, ETextureMap::Type arg_textureMapType);
	void setTextureId(void* arg_id);
};

} // namespace
