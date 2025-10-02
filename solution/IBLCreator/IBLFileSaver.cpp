#include "IBLFileSaver.h"
#include "Utils.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <filesystem>

namespace FS = std::filesystem;
void IBLFileSaver::generateIrradianceCrossMap(unsigned int sourceCubemapId, int faceSize)
{
	this->generateTextureFromCubemap(this->irradianceMapParams, sourceCubemapId, faceSize);
}

void IBLFileSaver::generatePrefilterMapParams(unsigned int sourceCubemapId, int faceSize)
{
	this->generateTextureFromCubemap(this->prefilterMapParams, sourceCubemapId, faceSize);
}

void IBLFileSaver::generateBRDFLUTMapParams(unsigned int textureId, int size)
{
	this->brdfLUTMapParams.textureId = textureId;
	this->brdfLUTMapParams.width = size;
	this->brdfLUTMapParams.height = size;
}

void IBLFileSaver::save(const char* sourceFilePath, const char* destinationPath)
{
	FS::path sourcePath{ sourceFilePath };
	FS::path fileName = sourcePath.stem().string() + "_irradiance.hdr";
	FS::path destinationPathFile = FS::path{ destinationPath } / fileName;

	const int irradianceDataSize = this->irradianceMapParams.width * this->irradianceMapParams.height * 3;
	std::vector<float> data(irradianceDataSize);

	glBindTexture(GL_TEXTURE_2D, this->irradianceMapParams.textureId);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, data.data());

	Utils::saveHdrTexture(this->irradianceMapParams.width, this->irradianceMapParams.height, 3, destinationPathFile.string(), data);
	glDeleteTextures(1, &this->irradianceMapParams.textureId);

	fileName = sourcePath.stem().string() + "_preFilter.hdr";
	destinationPathFile = FS::path{ destinationPath } / fileName;

	const int prefilterDataSize = this->prefilterMapParams.width * this->prefilterMapParams.height * 3;
	data.clear();
	data.resize(prefilterDataSize);

	glBindTexture(GL_TEXTURE_2D, this->prefilterMapParams.textureId);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, data.data());

	Utils::saveHdrTexture(this->prefilterMapParams.width, this->prefilterMapParams.height, 3, destinationPathFile.string(), data);
	glDeleteTextures(1, &this->prefilterMapParams.textureId);

	fileName = sourcePath.stem().string() + "_brdf.hdr";
	destinationPathFile = FS::path{ destinationPath } / fileName;

	size_t brdfLUTDataSize = this->brdfLUTMapParams.width * this->brdfLUTMapParams.height * 2;

	data.clear();
	data.resize(brdfLUTDataSize);

	glBindTexture(GL_TEXTURE_2D, this->brdfLUTMapParams.textureId);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RG, GL_FLOAT, data.data());

	const int CHANNELS_HDR = 3;
	int width = this->brdfLUTMapParams.width;
	int height = this->brdfLUTMapParams.height;
	std::vector<float> brdfResultData(width * height * CHANNELS_HDR);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int src_index = (y * width + x) * 2;
			int dst_index = (y * width + x) * CHANNELS_HDR;

			brdfResultData[dst_index + 0] = data[src_index + 0]; // R
			brdfResultData[dst_index + 1] = data[src_index + 1]; // G
			
			brdfResultData[dst_index + 2] = 0.0f;
		}
	}


	Utils::saveHdrTexture(this->brdfLUTMapParams.width, this->brdfLUTMapParams.height, CHANNELS_HDR, destinationPathFile.string(), brdfResultData);
	glDeleteTextures(1, &this->brdfLUTMapParams.textureId);
}

void IBLFileSaver::generateTextureFromCubemap(TextureMapParams& mapParams, unsigned int sourceCubemapId, int faceSize)
{
	const int WIDTH = 3 * faceSize;
	const int HEIGHT = 4 * faceSize;

	// --- 1. CRIAÇÃO DE RECURSOS ---
	unsigned int finalFBO;

	glGenFramebuffers(1, &finalFBO);
	glGenTextures(1, &mapParams.textureId);

	glBindTexture(GL_TEXTURE_2D, mapParams.textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WIDTH, HEIGHT, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, finalFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mapParams.textureId, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		glDeleteTextures(1, &mapParams.textureId);
		glDeleteFramebuffers(1, &finalFBO);
		throw std::runtime_error("Erro: Framebuffer não está completo!");
	}

	// --- 2. CÓPIA (PROCESSAMENTO) ---
	for (unsigned int i = 0; i < 6; ++i)
	{
		GLint dstX_offset = 0;
		GLint dstY_offset = 0;

		if (i == 0) { /* +X */ dstX_offset = 2 * faceSize; dstY_offset = 1 * faceSize; }
		else if (i == 1) { /* -X */ dstX_offset = 0 * faceSize; dstY_offset = 1 * faceSize; }
		else if (i == 2) { /* +Y */ dstX_offset = 1 * faceSize; dstY_offset = 0 * faceSize; }
		else if (i == 3) { /* -Y */ dstX_offset = 1 * faceSize; dstY_offset = 2 * faceSize; }
		else if (i == 4) { /* +Z */ dstX_offset = 1 * faceSize; dstY_offset = 1 * faceSize; }
		else if (i == 5) { /* -Z */ dstX_offset = 1 * faceSize; dstY_offset = 3 * faceSize; }

		glCopyImageSubData
		(
			sourceCubemapId, GL_TEXTURE_CUBE_MAP, 0, 0, 0, i, // Fonte: Cubemap Face i
			mapParams.textureId, GL_TEXTURE_2D, 0, dstX_offset, dstY_offset, 0, // Destino: Textura 2D
			faceSize, faceSize, 1
		);
	}

	glDeleteFramebuffers(1, &finalFBO);

	mapParams.width = WIDTH;
	mapParams.height = HEIGHT;
}
