#pragma once

#include "AEditorProperty.h"

namespace sre
{

class IntEditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	int* value;

public:
	SRE_API IntEditorProperty(const char* title, int* arg_value);
};

} // namespace
