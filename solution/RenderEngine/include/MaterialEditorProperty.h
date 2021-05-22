#pragma once

#include "AEditorProperty.h"

namespace sre
{

class MaterialEditorProperty : public AEditorProperty
{
private:
	class Material* material;

public:
	MaterialEditorProperty(const char* title, class Material* arg_material);

	void draw() override;
};

} // namespace
