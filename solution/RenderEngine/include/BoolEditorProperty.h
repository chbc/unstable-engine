#pragma once

#include "AEditorProperty.h"

namespace sre
{

class BoolEditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	bool* value;

public:
	SRE_API BoolEditorProperty(const char* title, bool* arg_value);
};

} // namespace
