#pragma once

#include "AEditorProperty.h"
#include "memory_aliases.h"

namespace sre
{

class ABaseMaterial;

class MaterialEditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	ABaseMaterial** value;

public:
	MaterialEditorProperty(const char* title, ABaseMaterial** arg_value);
	void draw() override;

private:
	void drawSubProperties();
	void reloadMaterial(const char* filePath);
};

} // namespace
