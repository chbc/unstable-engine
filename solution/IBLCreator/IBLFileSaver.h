#pragma once

struct TextureMapParams
{
	unsigned int textureId{ 0 };
	int width{ 0 };
	int height{ 0 };
};

class IBLFileSaver
{
private:
	TextureMapParams irradianceMapParams;
	TextureMapParams prefilterMapParams;
	TextureMapParams brdfLUTMapParams;

public:
	void setIrradianceMapParams(unsigned int textureId, int size);
	void setPrefilterMapParams(unsigned int textureId, int size);
	void setBRDFLUTMapParams(unsigned int textureId, int size);
	void save(const char* sourceFilePath, const char* destinationPath);
};
