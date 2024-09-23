#pragma once
#pragma once

#include "AEditorProperty.h"
#include "memory_aliases.h"
#include "MeshData.h"

namespace sre
{

class MeshEditorProperty : public AEditorProperty
{
private:
	UPTR<AMeshData>* meshData;

public:
	MeshEditorProperty(const char* title, UPTR<AMeshData>* arg_meshData);

	void draw() override;
	void serialize(c4::yml::NodeRef& propertyNode) override;
	void deserialize(c4::yml::ConstNodeRef& propertyNode) override;

};

} // namespace
