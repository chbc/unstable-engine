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
	EGuizmoType guizmoType{ EGuizmoType::MESH };

public:
	GuizmoComponent(Entity* entity);
	void loadMesh(EGuizmoType guizmoType);

friend class GuizmoRenderer;
};

} // namespace
