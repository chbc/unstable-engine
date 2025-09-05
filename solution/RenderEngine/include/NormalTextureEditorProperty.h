#pragma once

#include "TextureEditorProperty.h"

namespace sre
{

class NormalTextureEditorProperty : public TextureEditorProperty
{
DECLARE_PROPERTY()

public:
	NormalTextureEditorProperty(const char* title, Texture** arg_texture);

private:
	bool flipGreenChannel{ false };

};

} // namespace
