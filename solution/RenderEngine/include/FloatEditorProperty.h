#pragma once

#include "AEditorProperty.h"

namespace sre
{

class FloatEditorProperty : public AEditorProperty
{
DECLARE_PROPERTY()

private:
	float* value;

public:
	SRE_API FloatEditorProperty(const char* title, float* arg_value);
};

} // namespace
