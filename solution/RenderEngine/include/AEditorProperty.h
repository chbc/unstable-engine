#pragma once

#include <sstream>

namespace sre
{

class AEditorProperty
{
protected:
	std::string title;

public:
	AEditorProperty(const char* arg_title) : title(arg_title) { }

	virtual void draw() = 0;
	virtual void parseValue(std::ostringstream& result, bool& isSequence) {}

friend class ComponentParser;
};

} // namespace
