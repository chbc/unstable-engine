#pragma once

#include <string>

namespace sre
{

struct FileItem
{
	std::string fileName;
	void* textureId = nullptr;

	FileItem(const char* arg_fileName, void* arg_textureId);
};

} // namespace
