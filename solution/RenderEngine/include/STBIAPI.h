#pragma once

#include "AHDRTexturesWrapper.h"

namespace sre
{

class STBIAPI : public AHDRTexturesWrapper
{
public:
	STBIAPI() = default;

protected:
	void init() override;
	float* load(const std::string& filePath, int* outWidth, int* outHeight, int* outBpp) override;
};

} // namespace
