#pragma once

#include <string>

namespace sre
{

class AHDRTexturesWrapper
{
protected:
	AHDRTexturesWrapper() = default;

public:
	virtual ~AHDRTexturesWrapper() = default;

protected:
	virtual void init() = 0;
	virtual float* load(const std::string& filePath, int* outWidth, int* outHeight, int* outBpp) = 0;

friend class MultimediaManager;
};

} // namespace
