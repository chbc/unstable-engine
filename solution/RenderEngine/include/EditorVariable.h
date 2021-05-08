#pragma once

#include <unordered_map>
#include <string>
#include <tuple>
#include "memory_aliases.h"
#include "TypeId.h"

namespace sre
{

class EditorVariable
{
public:
	const std::string title;
	std::string label;
	const TypeId::Type typeId;
	SPTR<void> pointer;

public:
	EditorVariable(const char* arg_title, TypeId::Type arg_typeId, void* arg_pointer)
		: title(arg_title), typeId(arg_typeId), pointer(arg_pointer)
	{
		this->label = "##" + this->title;
	}
};

} // namespace
