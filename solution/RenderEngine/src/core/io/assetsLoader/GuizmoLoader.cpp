#include "GuizmoLoader.h"
#include "SingletonsManager.h"
#include "AGraphicsWrapper.h"
#include "PrimitiveMeshFactory.h"

namespace sre
{

ColorMeshData* GuizmoLoader::load(const std::string& type)
{
	return PrimitiveMeshFactory().createBoxLines(glm::vec4{ 1.0 });
}

void GuizmoLoader::release(ColorMeshData* mesh)
{
	AGraphicsWrapper* graphicsWrapper = SingletonsManager::getInstance()->get<AGraphicsWrapper>();
	graphicsWrapper->deleteBuffers(mesh);
}

} // namespace
