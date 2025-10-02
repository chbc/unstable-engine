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
	void generateIrradianceCrossMap(unsigned int sourceCubemapId, int faceSize);
	void generatePrefilterMapParams(unsigned int sourceCubemapId, int faceSize);
	void generateBRDFLUTMapParams(unsigned int textureId, int size);
	void save(const char* sourceFilePath, const char* destinationPath);

private:
	void generateTextureFromCubemap(TextureMapParams& mapParams, unsigned int sourceCubemapId, int faceSize);
};
