#pragma once

#include "AEditorProperty.h"

namespace sre
{

class TextureEditorProperty : public AEditorProperty
{

private:
	void* value;

public:
	TextureEditorProperty(const char* title, uint32_t arg_value);

	void draw() override;
};

} // namespace
