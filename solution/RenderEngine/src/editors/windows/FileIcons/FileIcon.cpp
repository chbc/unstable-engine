#include "FileIcon.h"
#include "FileUtils.h"

namespace sre
{

FileIcon::FileIcon(std::string arg_filePath, void* arg_textureId)
	: filePath{ arg_filePath }, textureId{ reinterpret_cast<uint64_t>(arg_textureId) }
{
	this->fileName = FileUtils::getFileName(this->filePath);
}

} // namespace
