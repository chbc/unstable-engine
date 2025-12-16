#pragma once

#include <string>

namespace sre
{

class AAsset
{
protected:
	std::string filePath;

public:
	AAsset(const std::string& arg_filePath);
	virtual ~AAsset() = default;
	const std::string& getFilePath() const;
};

} // namespace
