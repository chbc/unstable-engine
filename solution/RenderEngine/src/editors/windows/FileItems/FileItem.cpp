#include "FileItem.h"

namespace sre
{

FileItem::FileItem(const char* arg_fileName, void* arg_textureId)
	: fileName{arg_fileName}, textureId(arg_textureId)
{ }

} // namespace
