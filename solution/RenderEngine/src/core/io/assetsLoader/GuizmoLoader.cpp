#include "GuizmoLoader.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "PrimitiveMeshFactory.h"

namespace sre
{

ColorMeshData* GuizmoLoader::load(EGuizmoType type)
{
	ColorMeshData* result = nullptr;
	PrimitiveMeshFactory factory;
	switch (type)
	{
		case EGuizmoType::MESH:
			result = factory.createBoxLines(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });
			break;
		case EGuizmoType::BOX_COLLISION:
			result = factory.createBoxLines(glm::vec4{ 0.25f, 1.0f, 0.25f, 1.0f });
			break;
		case EGuizmoType::SPHERE_COLLISION:
			result = factory.createSphereLines(0.5f, glm::vec4{ 0.25f, 1.0f, 0.25f, 1.0f });
			break;
	}

	return result;
}

void GuizmoLoader::release(ColorMeshData* mesh)
{
	AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
	graphicsWrapper->deleteBuffers(mesh);
}

} // namespace
