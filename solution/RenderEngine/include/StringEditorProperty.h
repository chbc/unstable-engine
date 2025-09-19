#pragma once

#include "AEditorProperty.h"

namespace sre
{

class StringEditorProperty : public AEditorProperty
{

DECLARE_PROPERTY()

private:
	std::string text;

public:
	StringEditorProperty(const std::string& title, const std::string& arg_text);
};

} // namespace
