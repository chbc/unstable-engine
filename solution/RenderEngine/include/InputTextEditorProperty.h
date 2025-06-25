#pragma once

#include "AEditorProperty.h"

namespace sre
{

class InputTextEditorProperty : public AEditorProperty
{

DECLARE_PROPERTY()

private:
	std::string* text{ nullptr };

public:
	InputTextEditorProperty(const char* title, std::string* arg_text);
};

} // namespace
