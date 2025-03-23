#include "FileIcon.h"
#include "FileUtils.h"

namespace sre
{

FileIcon::FileIcon(std::string arg_filePath, void* arg_textureId)
	: filePath{ arg_filePath }, textureId{ arg_textureId }
{
	this->filePath = FileUtils::getFileName(this->filePath);
}

} // namespace
