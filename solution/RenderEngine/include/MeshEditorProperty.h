#pragma once

#include "AEditorProperty.h"

#include <string>

namespace sre
{

struct MeshData;

class MeshEditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	MeshData** value;
	std::string* modelPath;

public:
	MeshEditorProperty(const char* title, MeshData** arg_value, std::string* arg_modelPath);
};

} // namespace
