#pragma once

#include "ARenderableComponent.h"
#include "ColorMeshData.h"
#include "EGuizmoMesh.h"

namespace sre
{

class SRE_API GuizmoComponent : public ARenderableComponent
{
DECLARE_COMPONENT()

private:
	ColorMeshData* mesh{ nullptr };
	EGuizmoType guizmoType{ EGuizmoType::Mesh };

public:
	GuizmoComponent(Entity* entity);

friend class GuizmoRenderer;
};

} // namespace
