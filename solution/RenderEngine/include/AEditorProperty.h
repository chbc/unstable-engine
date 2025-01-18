#pragma once

#include <sstream>
#include <functional>

#include "core_defines.h"

namespace c4
{
	namespace yml
	{
		class NodeRef;
		class ConstNodeRef;
	}
}

namespace sre
{

class AEditorProperty
{
protected:
	std::string title;
	std::function<void(void)> onValueChanged;

public:
	AEditorProperty(const char* arg_title)
		: title(arg_title) { }

	virtual ~AEditorProperty() { }

	virtual void draw() = 0;
	virtual void serialize(c4::yml::NodeRef& propertyNode) = 0;
	virtual void deserialize(c4::yml::ConstNodeRef& propertyNode) = 0;

friend class Entity;
friend class ComponentParser;
friend class MaterialLoader;
friend class AEntityComponent;
};

} // namespace
