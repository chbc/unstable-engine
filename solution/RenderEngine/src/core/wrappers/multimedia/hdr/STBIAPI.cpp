#include "STBIAPI.h"
#include "FileUtils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stbi/stb_image.h"

namespace sre
{

void STBIAPI::init()
{
	stbi_set_flip_vertically_on_load(false);
}

float* STBIAPI::load(const std::string& filePath, int* outWidth, int* outHeight, int* outBpp)
{
	std::string absolutePath = FileUtils::getContentAbsolutePath(filePath);
	float* data = stbi_loadf(absolutePath.c_str(), outWidth, outHeight, outBpp, 0);
	return data;
}

} // namespace
