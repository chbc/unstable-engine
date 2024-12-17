#pragma once
#pragma once

#include "AEditorProperty.h"

namespace sre
{

struct Mesh;

class MeshEditorProperty : public AEditorProperty
{
private:
	std::string fileName;
	Mesh** mesh;

public:
	MeshEditorProperty(const char* title, Mesh** arg_mesh);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;
};

} // namespace
