#pragma once

#include <string>

namespace sre
{

class AEditorProperty
{
protected:
	std::string title;

public:
	AEditorProperty(const char* arg_title) : title(arg_title) { }

	virtual void draw() = 0;
};

} // namespace
