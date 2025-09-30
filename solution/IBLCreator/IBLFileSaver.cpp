#include "IBLFileSaver.h"
#include "Utils.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <filesystem>

namespace FS = std::filesystem;

void IBLFileSaver::setIrradianceMapParams(unsigned int textureId, int size)
{
	const int FS = size; // Tamanho da face do cubemap (Face Size - FS)
	const int WIDTH = 3 * FS; // Largura e Altura da imagem final (96x128 para o layout Cross)
	const int HEIGHT = 4 * FS;

	// Crie o FBO e a Textura para a Imagem 2D
	unsigned int finalFBO;
	unsigned int finalTexture2D;

	glGenFramebuffers(1, &finalFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, finalFBO);

	glGenTextures(1, &finalTexture2D);
	glBindTexture(GL_TEXTURE_2D, finalTexture2D);

	// Use o mesmo formato de alta precisão (GL_RGB16F)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WIDTH, HEIGHT, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Anexe a textura ao FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, finalTexture2D, 0);

	// Certifique-se de que o FBO está completo (opcional, mas recomendado)
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		throw "Erro: Framebuffer não está completo!";
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 4. Copiar as faces do Cubemap para a Textura 2D
	// Bind o FBO 2D
	glBindFramebuffer(GL_FRAMEBUFFER, finalFBO);
	glViewport(0, 0, WIDTH, HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT); // Limpa a textura final

	// Configure o 'irradianceMap' como a fonte de dados (fonte de leitura)
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	// As coordenadas de destino (xoffset, yoffset) na textura 2D (96x128):
	// Layout:
	//       | +Y (Cima) |
	//  -X   | +Z (Frente)| +X
	//       | -Y (Baixo) |
	//       | -Z (Trás)  |

// Tamanho da face (FS) e Textura 2D final (finalTexture2D)

	// Itere sobre as 6 faces
	for (unsigned int i = 0; i < 6; ++i)
	{
		// Define a face do Cubemap (Fonte)
		GLenum srcTarget = GL_TEXTURE_CUBE_MAP;
		GLint srcZ = i; // O índice Z define a face do cubemap (+X, -X, etc.)

		// Define a Textura 2D (Destino)
		GLenum dstTarget = GL_TEXTURE_2D;
		GLint dstZ = 0; // Textura 2D tem profundidade Z=0

		// Calcule os offsets X e Y de destino na textura 2D (mesmo layout 'Cross')
		GLint dstX_offset = 0;
		GLint dstY_offset = 0;

		// Baseado no índice i (0 a 5, que corresponde ao Pos_X, Neg_X, Pos_Y, etc.)
		if (i == 0)
		{ // +X
			dstX_offset = 2 * FS; dstY_offset = 1 * FS;
		}
		else if (i == 1)
		{ // -X
			dstX_offset = 0 * FS; dstY_offset = 1 * FS;
		}
		else if (i == 2)
		{ // +Y
			dstX_offset = 1 * FS; dstY_offset = 0 * FS;
		}
		else if (i == 3)
		{ // -Y
			dstX_offset = 1 * FS; dstY_offset = 2 * FS;
		}
		else if (i == 4)
		{ // +Z
			dstX_offset = 1 * FS; dstY_offset = 1 * FS;
		}
		else if (i == 5)
		{ // -Z
			dstX_offset = 1 * FS; dstY_offset = 3 * FS;
		}

		glCopyImageSubData(
			textureId, srcTarget, 0, 0, 0, srcZ, // Fonte: irradianceMap, nível 0, face Z=i
			finalTexture2D, dstTarget, 0, dstX_offset, dstY_offset, dstZ, // Destino: finalTexture2D, nível 0, offset calculado
			FS, FS, 1 // Largura, Altura, Profundidade (1 para 2D)
		);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // Desvincula o FBO



	this->irradianceMapParams.textureId = finalTexture2D;
	this->irradianceMapParams.width = WIDTH;
	this->irradianceMapParams.height = HEIGHT;
}

void IBLFileSaver::setPrefilterMapParams(unsigned int textureId, int size)
{
	const int FS = size; // Tamanho da face do cubemap (Face Size - FS)
	const int WIDTH = 3 * FS; // Largura e Altura da imagem final (96x128 para o layout Cross)
	const int HEIGHT = 4 * FS;

	// Crie o FBO e a Textura para a Imagem 2D
	unsigned int finalFBO;
	unsigned int finalTexture2D;

	glGenFramebuffers(1, &finalFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, finalFBO);

	glGenTextures(1, &finalTexture2D);
	glBindTexture(GL_TEXTURE_2D, finalTexture2D);

	// Use o mesmo formato de alta precisão (GL_RGB16F)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WIDTH, HEIGHT, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Anexe a textura ao FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, finalTexture2D, 0);

	// Certifique-se de que o FBO está completo (opcional, mas recomendado)
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		throw "Erro: Framebuffer não está completo!";
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 4. Copiar as faces do Cubemap para a Textura 2D
	// Bind o FBO 2D
	glBindFramebuffer(GL_FRAMEBUFFER, finalFBO);
	glViewport(0, 0, WIDTH, HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT); // Limpa a textura final

	// Configure o 'irradianceMap' como a fonte de dados (fonte de leitura)
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	// As coordenadas de destino (xoffset, yoffset) na textura 2D (96x128):
	// Layout:
	//       | +Y (Cima) |
	//  -X   | +Z (Frente)| +X
	//       | -Y (Baixo) |
	//       | -Z (Trás)  |

// Tamanho da face (FS) e Textura 2D final (finalTexture2D)

	// Itere sobre as 6 faces
	for (unsigned int i = 0; i < 6; ++i)
	{
		// Define a face do Cubemap (Fonte)
		GLenum srcTarget = GL_TEXTURE_CUBE_MAP;
		GLint srcZ = i; // O índice Z define a face do cubemap (+X, -X, etc.)

		// Define a Textura 2D (Destino)
		GLenum dstTarget = GL_TEXTURE_2D;
		GLint dstZ = 0; // Textura 2D tem profundidade Z=0

		// Calcule os offsets X e Y de destino na textura 2D (mesmo layout 'Cross')
		GLint dstX_offset = 0;
		GLint dstY_offset = 0;

		// Baseado no índice i (0 a 5, que corresponde ao Pos_X, Neg_X, Pos_Y, etc.)
		if (i == 0)
		{ // +X
			dstX_offset = 2 * FS; dstY_offset = 1 * FS;
		}
		else if (i == 1)
		{ // -X
			dstX_offset = 0 * FS; dstY_offset = 1 * FS;
		}
		else if (i == 2)
		{ // +Y
			dstX_offset = 1 * FS; dstY_offset = 0 * FS;
		}
		else if (i == 3)
		{ // -Y
			dstX_offset = 1 * FS; dstY_offset = 2 * FS;
		}
		else if (i == 4)
		{ // +Z
			dstX_offset = 1 * FS; dstY_offset = 1 * FS;
		}
		else if (i == 5)
		{ // -Z
			dstX_offset = 1 * FS; dstY_offset = 3 * FS;
		}

		glCopyImageSubData(
			textureId, srcTarget, 0, 0, 0, srcZ, // Fonte: irradianceMap, nível 0, face Z=i
			finalTexture2D, dstTarget, 0, dstX_offset, dstY_offset, dstZ, // Destino: finalTexture2D, nível 0, offset calculado
			FS, FS, 1 // Largura, Altura, Profundidade (1 para 2D)
		);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // Desvincula o FBO



	this->prefilterMapParams.textureId = finalTexture2D;
	this->prefilterMapParams.width = WIDTH;
	this->prefilterMapParams.height = HEIGHT;
}

void IBLFileSaver::setBRDFLUTMapParams(unsigned int textureId, int size)
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
	float* data = new float[irradianceDataSize];

	glBindTexture(GL_TEXTURE_2D, this->irradianceMapParams.textureId);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, data);

	Utils::saveHdrTexture(this->irradianceMapParams.width, this->irradianceMapParams.height, destinationPathFile.string(), data);
	delete[] data;



	fileName = sourcePath.stem().string() + "_preFilter.hdr";
	destinationPathFile = FS::path{ destinationPath } / fileName;

	const int prefilterDataSize = this->prefilterMapParams.width * this->prefilterMapParams.height * 3;
	data = new float[prefilterDataSize];

	glBindTexture(GL_TEXTURE_2D, this->prefilterMapParams.textureId);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, data);

	Utils::saveHdrTexture(this->prefilterMapParams.width, this->prefilterMapParams.height, destinationPathFile.string(), data);
	delete[] data;
}
