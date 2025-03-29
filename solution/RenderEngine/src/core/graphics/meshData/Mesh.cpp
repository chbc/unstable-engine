#include "Mesh.h"
#include "FileUtils.h"

namespace sre
{

Mesh::Mesh(AMeshData* arg_meshData, const char* arg_filePath)
{
	this->filePath = FileUtils::getContentRelativePath(arg_filePath);
	meshData.reset(arg_meshData);
}

const std::string& Mesh::getFilePath()
{
	return this->filePath;
}

} // namespace
