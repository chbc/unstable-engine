#pragma once

#include <string>

namespace sre
{

struct FileIcon
{
	std::string filePath;
	std::string fileName;
	uint64_t textureId{ 0 };

	FileIcon(std::string arg_filePath, void* arg_textureId);
};

} // namespace
