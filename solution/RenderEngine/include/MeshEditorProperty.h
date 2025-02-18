#pragma once
#pragma once

#include "AEditorProperty.h"

namespace sre
{

struct Mesh;

class MeshEditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	Mesh** value;

public:
	MeshEditorProperty(const char* title, Mesh** arg_value);
};

} // namespace
