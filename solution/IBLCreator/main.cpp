#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Utils.h"
#include "IBLFileSaver.h"

// pbr: set up projection and view matrices for capturing data onto the 6 cubemap face directions
// ----------------------------------------------------------------------------------------------
glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
glm::mat4 captureViews[] =
{
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
    glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
};

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

unsigned int envCubemap{ 0 };
unsigned int captureFBO{ 0 };
unsigned int captureRBO{ 0 };

SDL_Window* window{ nullptr };

IBLFileSaver iblFileSaver;

int setupWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow
    (
        "Irradiance Converter",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCR_WIDTH, SCR_HEIGHT,
        flags
    );

    if (window == NULL)
    {
        return 2;
    }

    if (SDL_GL_CreateContext(window) == NULL)
    {
        return 3;
    }

    // GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        return 4;
    }

    return 0;
}

void setupHdr(const char* hdrPath)
{
    // pbr: setup cubemap to render to and attach to framebuffer
    // ---------------------------------------------------------
    glGenTextures(1, &envCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // pbr: setup framebuffer
    // ----------------------
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

    // pbr: load the HDR environment map
    // ---------------------------------

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    // ----------------------------------------------------------------------
	uint32_t equirectangularToCubemapProgram = Utils::createShader("../content/engine/shaders/pbr/cubemap.vert", "../content/engine/shaders/pbr/equirectangular_to_cubemap.frag");
    glUseProgram(equirectangularToCubemapProgram);
    glUniform1d(glGetUniformLocation(equirectangularToCubemapProgram, "equirectangularMap"), 0);
    glUniformMatrix4fv(glGetUniformLocation(equirectangularToCubemapProgram, "projectionMatrix"), 1, GL_FALSE, &captureProjection[0][0]);

    glActiveTexture(GL_TEXTURE0);
    unsigned int hdrTexture = Utils::loadHdrTexture(hdrPath);
    glBindTexture(GL_TEXTURE_2D, hdrTexture);

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glUniformMatrix4fv(glGetUniformLocation(equirectangularToCubemapProgram, "viewMatrix"), 1, GL_FALSE, &captureViews[i][0][0]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Utils::renderCube();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    glDeleteProgram(equirectangularToCubemapProgram);
    glDeleteTextures(1, &hdrTexture);

	iblFileSaver.generateHdrCrossMap(envCubemap, 512);
}

void setupIrradianceMap()
{
    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    // --------------------------------------------------------------------------------
    unsigned int irradianceMap{ 0 };
    glGenTextures(1, &irradianceMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);


	uint32_t irradianceProgram = Utils::createShader("../content/engine/shaders/pbr/cubemap.vert", "../content/engine/shaders/pbr/irradiance_convolution.frag");
    glUseProgram(irradianceProgram);
    glUniform1i(glGetUniformLocation(irradianceProgram, "environmentMap"), 0);
    glUniformMatrix4fv(glGetUniformLocation(irradianceProgram, "projectionMatrix"), 1, GL_FALSE, &captureProjection[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32);
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glUniformMatrix4fv(glGetUniformLocation(irradianceProgram, "viewMatrix"), 1, GL_FALSE, &captureViews[i][0][0]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Utils::renderCube();
    }
    // Desvincula o FBO de captura (prática recomendada)
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Chamamos a nova função de geração:
    iblFileSaver.generateIrradianceCrossMap(irradianceMap, 32);

    glDeleteProgram(irradianceProgram);
    glDeleteTextures(1, &irradianceMap);
}

void setupPrefilterMap()
{
    // pbr: create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale.
    // --------------------------------------------------------------------------------
    unsigned int prefilterMap{ 0 };
    glGenTextures(1, &prefilterMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // be sure to set minification filter to mip_linear 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // generate mipmaps for the cubemap so OpenGL automatically allocates the required memory.
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    // pbr: run a quasi monte-carlo simulation on the environment lighting to create a prefilter (cube)map.
     // ----------------------------------------------------------------------------------------------------
	uint32_t prefilterProgram = Utils::createShader("../content/engine/shaders/pbr/cubemap.vert", "../content/engine/shaders/pbr/prefilter.frag");
    glUseProgram(prefilterProgram);
    glUniform1i(glGetUniformLocation(prefilterProgram, "environmentMap"), 0);
    glUniformMatrix4fv(glGetUniformLocation(prefilterProgram, "projectionMatrix"), 1, GL_FALSE, &captureProjection[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    unsigned int maxMipLevels = 5;
    for (unsigned int mip = 0; mip < maxMipLevels; ++mip)
    {
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        unsigned int mipHeight = static_cast<unsigned int>(128 * std::pow(0.5, mip));
        glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight);
        glViewport(0, 0, mipWidth, mipHeight);

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        glUniform1f(glGetUniformLocation(prefilterProgram, "roughness"), roughness);
        for (unsigned int i = 0; i < 6; ++i)
        {
            glUniformMatrix4fv(glGetUniformLocation(prefilterProgram, "viewMatrix"), 1, GL_FALSE, &captureViews[i][0][0]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Utils::renderCube();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	iblFileSaver.generatePrefilterCrossMap(prefilterMap, 128);

    glDeleteProgram(prefilterProgram);
    glDeleteTextures(1, &prefilterMap);
}

void setupBRDFLUTMap(unsigned int textureMap)
{
    // pbr: generate a 2D LUT from the BRDF equations used.
    // ----------------------------------------------------
    glGenTextures(1, &textureMap);

    // pre-allocate enough memory for the LUT texture.
    glBindTexture(GL_TEXTURE_2D, textureMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
    // be sure to set wrapping mode to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // then re-configure capture framebuffer object and render screen-space quad with BRDF shader.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureMap, 0);

    glViewport(0, 0, 512, 512);
    uint32_t brdfProgram = Utils::createShader("../content/engine/shaders/pbr/brdf.vert", "../content/engine/shaders/pbr/brdf.frag");
    glUseProgram(brdfProgram);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Utils::renderQuad();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	iblFileSaver.generateBRDFLUTMapParams(textureMap, 512);

    glDeleteProgram(brdfProgram);
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
#ifdef DEBUG
        std::cout << "Usage: IBLCreator.exe [source_file] [destination_path]" << std::endl;
#endif
        return 1;
    }

	int result = setupWindow();
    if (result != 0)
    {
        return result;
    }

	const char* sourceFilePath = argv[1];
	const char* destinationPath = argv[2];

    setupHdr(sourceFilePath);
    setupIrradianceMap();
    setupPrefilterMap();

    unsigned int brdfLUTMap{ 0 };
    setupBRDFLUTMap(brdfLUTMap);

    iblFileSaver.save(sourceFilePath, destinationPath);

    glDeleteTextures(1, &brdfLUTMap);
    glDeleteTextures(1, &envCubemap);
    glDeleteRenderbuffers(1, &captureRBO);
    glDeleteFramebuffers(1, &captureFBO);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
