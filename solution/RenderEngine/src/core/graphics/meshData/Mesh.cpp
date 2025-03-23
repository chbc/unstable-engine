#include "Mesh.h"

namespace sre
{

Mesh::Mesh(AMeshData* arg_meshData, const char* arg_filePath) : filePath(arg_filePath)
{
	meshData.reset(arg_meshData);
}

} // namespace
