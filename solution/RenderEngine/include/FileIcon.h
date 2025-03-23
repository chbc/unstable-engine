#pragma once

#include <string>

namespace sre
{

struct FileIcon
{
	std::string filePath;
	void* textureId = nullptr;

	FileIcon(std::string arg_filePath, void* arg_textureId);
};

} // namespace
