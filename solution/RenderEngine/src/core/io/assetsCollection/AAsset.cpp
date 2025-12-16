#include "AAsset.h"

namespace sre
{

AAsset::AAsset(const std::string& arg_filePath)
	: filePath(arg_filePath)
{ }

const std::string& AAsset::getFilePath() const
{
	return this->filePath;
}

} // namespace
