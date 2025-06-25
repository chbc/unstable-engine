#pragma once

#include "AEditorProperty.h"

namespace sre
{

class FontAtlas;
struct MeshData2D;

class FontEditorProperty : public AEditorProperty
{

DECLARE_PROPERTY()

private:
	FontAtlas** fontAtlas{ nullptr };
	std::string filePath;

public:
	FontEditorProperty(const char* title, FontAtlas** arg_fontAtlas);
};

} // namespace
