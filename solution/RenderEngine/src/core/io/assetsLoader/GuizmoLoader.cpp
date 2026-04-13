#include "GuizmoLoader.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "PrimitiveMeshFactory.h"

namespace sre
{

ColorMeshData* GuizmoLoader::load(EGuizmoType type)
{
	glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };
	if (type == EGuizmoType::Collision)
	{
		color = glm::vec4{ 0.25f, 1.0f, 0.25f, 1.0f };
	}

	return PrimitiveMeshFactory().createBoxLines(color);
}

void GuizmoLoader::release(ColorMeshData* mesh)
{
	AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
	graphicsWrapper->deleteBuffers(mesh);
}

} // namespace
