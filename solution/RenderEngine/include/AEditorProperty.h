#pragma once

#include <string>

namespace sre
{

class AEditorProperty
{
public:
	std::string title;

public:
	AEditorProperty(const char* arg_title) : title(arg_title) { }

	virtual void draw() = 0;
};

} // namespace
