#pragma once
#pragma once

#include "AEditorProperty.h"
#include "Mesh.h"

namespace sre
{

class MeshEditorProperty : public AEditorProperty
{
private:
	UPTR<Mesh>* mesh;
	std::string fileName;

public:
	MeshEditorProperty(const char* title, UPTR<Mesh>* arg_mesh);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;

};

} // namespace
