#include "Mesh.h"

namespace sre
{

Mesh::Mesh(AMeshData* arg_meshData, const char* arg_fileName) : fileName(arg_fileName)
{
	meshData.reset(arg_meshData);
}

} // namespace
