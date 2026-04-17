#pragma once

#include "ARenderableComponent.h"
#include "ColorMeshData.h"
#include "EGuizmoMesh.h"

namespace sre
{

class AColliderComponent;

class SRE_API GuizmoComponent : public ARenderableComponent
{
DECLARE_COMPONENT()

private:
	ColorMeshData* mesh{ nullptr };
	EGuizmoType guizmoType{ EGuizmoType::MESH };
	size_t colliderCallbackId{ 0 };
	AColliderComponent* subjectCollider{ nullptr };

public:
	GuizmoComponent(Entity* entity);
	~GuizmoComponent();

	void loadMesh(EGuizmoType guizmoType, AColliderComponent* arg_subjectCollider = nullptr);

private:
	void onColliderChanged();

friend class GuizmoRenderer;
};

} // namespace
