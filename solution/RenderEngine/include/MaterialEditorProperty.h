#pragma once

#include "AEditorProperty.h"
#include "memory_aliases.h"

namespace sre
{

class Material;

class MaterialEditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	Material** value;

public:
	MaterialEditorProperty(const char* title, Material** arg_value);
	void draw() override;

private:
	void drawSubProperties();
	void reloadMaterial(const char* filePath);
};

} // namespace
