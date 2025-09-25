#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Utils.h"


// lights
// ------
glm::vec3 lightPositions[] =
{
    glm::vec3(-10.0f,  10.0f, 10.0f),
    glm::vec3(10.0f,  10.0f, 10.0f),
    glm::vec3(-10.0f, -10.0f, 10.0f),
    glm::vec3(10.0f, -10.0f, 10.0f),
};
glm::vec3 lightColors[] =
{
    glm::vec3(300.0f, 300.0f, 300.0f),
    glm::vec3(300.0f, 300.0f, 300.0f),
    glm::vec3(300.0f, 300.0f, 300.0f),
    glm::vec3(300.0f, 300.0f, 300.0f)
};

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

uint32_t backgroundProgram{ 0 };
unsigned int envCubemap{ 0 };
unsigned int captureFBO{ 0 };
unsigned int captureRBO{ 0 };

unsigned int irradianceMap{ 0 };

void setupFramebuffer()
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
}

void setupHdr()
{
    // pbr: load the HDR environment map
    // ---------------------------------

    // pbr: convert HDR equirectangular environment map to cubemap equivalent
    // ----------------------------------------------------------------------
	uint32_t equirectangularToCubemapProgram = Utils::createShader("../content/engine/shaders/irradiance/cubemap.vert", "../content/engine/shaders/irradiance/equirectangular_to_cubemap.frag");
    glUseProgram(equirectangularToCubemapProgram);
    glUniform1d(glGetUniformLocation(equirectangularToCubemapProgram, "equirectangularMap"), 0);
    glUniformMatrix4fv(glGetUniformLocation(equirectangularToCubemapProgram, "projection"), 1, GL_FALSE, &captureProjection[0][0]);

    glActiveTexture(GL_TEXTURE0);
    unsigned int hdrTexture = Utils::loadHdrTexture("../content/engine/media/hdr/newport_loft.hdr");
    glBindTexture(GL_TEXTURE_2D, hdrTexture);

    glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glUniformMatrix4fv(glGetUniformLocation(equirectangularToCubemapProgram, "view"), 1, GL_FALSE, &captureViews[i][0][0]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Utils::renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // then let OpenGL generate mipmaps from first mip face (combatting visible dots artifact)
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

void setupSkybox()
{
    backgroundProgram = Utils::createShader("../content/engine/shaders/irradiance/background.vert", "../content/engine/shaders/irradiance/background.frag");

    glUseProgram(backgroundProgram);
    glUniform1i(glGetUniformLocation(backgroundProgram, "environmentMap"), 0);
}

void renderSkybox(const glm::mat4& projection, const glm::mat4& view)
{
    glUseProgram(backgroundProgram);
    glUniformMatrix4fv(glGetUniformLocation(backgroundProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(backgroundProgram, "view"), 1, GL_FALSE, &view[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
    Utils::renderCube();
}

void setupIrradianceMap()
{
    // pbr: create an irradiance cubemap, and re-scale capture FBO to irradiance scale.
    // --------------------------------------------------------------------------------
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


	uint32_t irradianceProgram = Utils::createShader("../content/engine/shaders/irradiance/cubemap.vert", "../content/engine/shaders/irradiance/irradiance_convolution.frag");
    glUseProgram(irradianceProgram);
    glUniform1i(glGetUniformLocation(irradianceProgram, "environmentMap"), 0);
    glUniformMatrix4fv(glGetUniformLocation(irradianceProgram, "projection"), 1, GL_FALSE, &captureProjection[0][0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

    glViewport(0, 0, 32, 32); // don't forget to configure the viewport to the capture dimensions.
    glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
    for (unsigned int i = 0; i < 6; ++i)
    {
        glUniformMatrix4fv(glGetUniformLocation(irradianceProgram, "view"), 1, GL_FALSE, &captureViews[i][0][0]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Utils::renderCube();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    SDL_Window* window = SDL_CreateWindow
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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	uint32_t pbrProgram = Utils::createShader("../content/engine/shaders/irradiance/pbr.vert", "../content/engine/shaders/irradiance/pbr.frag");
	uint32_t prefilterProgram = Utils::createShader("../content/engine/shaders/irradiance/cubemap.vert", "../content/engine/shaders/irradiance/prefilter.frag");
	uint32_t brdfProgram = Utils::createShader("../content/engine/shaders/irradiance/brdf.vert", "../content/engine/shaders/irradiance/brdf.frag");


	glUseProgram(pbrProgram);
	glUniform1i(glGetUniformLocation(pbrProgram, "irradianceMap"), 0);
	glUniform1i(glGetUniformLocation(pbrProgram, "prefilterMap"), 1);
	glUniform1i(glGetUniformLocation(pbrProgram, "brdfLUT"), 2);
	glUniform1i(glGetUniformLocation(pbrProgram, "albedoMap"), 3);
	glUniform1i(glGetUniformLocation(pbrProgram, "normalMap"), 4);
	glUniform1i(glGetUniformLocation(pbrProgram, "metallicMap"), 5);
	glUniform1i(glGetUniformLocation(pbrProgram, "roughnessMap"), 6);
	glUniform1i(glGetUniformLocation(pbrProgram, "aoMap"), 7);

	setupSkybox();

    // load PBR material textures
    // --------------------------
    // rusted iron
    unsigned int ironAlbedoMap = Utils::loadTexture("../content/game/pbr/rusted_iron/albedo.png");
    unsigned int ironNormalMap = Utils::loadTexture("../content/game/pbr/rusted_iron/normal.png");
    unsigned int ironMetallicMap = Utils::loadTexture("../content/game/pbr/rusted_iron/metallic.png");
    unsigned int ironRoughnessMap = Utils::loadTexture("../content/game/pbr/rusted_iron/roughness.png");
    unsigned int ironAOMap = Utils::loadTexture("../content/game/pbr/rusted_iron/ao.png");

    setupFramebuffer();
    setupHdr();
    setupIrradianceMap();

    // pbr: create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale.
    // --------------------------------------------------------------------------------
    unsigned int prefilterMap;
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
	glUseProgram(prefilterProgram);
	glUniform1i(glGetUniformLocation(prefilterProgram, "environmentMap"), 0);
	glUniformMatrix4fv(glGetUniformLocation(prefilterProgram, "projection"), 1, GL_FALSE, &captureProjection[0][0]);
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
			glUniformMatrix4fv(glGetUniformLocation(prefilterProgram, "view"), 1, GL_FALSE, &captureViews[i][0][0]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Utils::renderCube();
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // pbr: generate a 2D LUT from the BRDF equations used.
    // ----------------------------------------------------
    unsigned int brdfLUTTexture;
    glGenTextures(1, &brdfLUTTexture);

    // pre-allocate enough memory for the LUT texture.
    glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);
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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0);

    glViewport(0, 0, 512, 512);
	glUseProgram(brdfProgram);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Utils::renderQuad();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // initialize static shader uniforms before rendering
    // --------------------------------------------------
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glUseProgram(pbrProgram);
    glUniformMatrix4fv(glGetUniformLocation(pbrProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

    int drawableWidth, drawableHeight;
    SDL_GL_GetDrawableSize(window, &drawableWidth, &drawableHeight);
    glViewport(0, 0, drawableWidth, drawableHeight);

    // render loop
    // -----------
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render scene, supplying the convoluted irradiance map to the final shader.
        // ------------------------------------------------------------------------------------------
        glm::mat4 view = glm::lookAt(glm::vec3{ 0.0f, 0.0f, 10.0f }, glm::vec3{0.0f}, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::mat4 model = glm::mat4(1.0f);
		glm::vec3 cameraPosition{ 0.0f, 0.0f, 10.0f };
		glUseProgram(pbrProgram);
		glUniformMatrix4fv(glGetUniformLocation(pbrProgram, "view"), 1, GL_FALSE, &view[0][0]);
        glUniform3fv(glGetUniformLocation(pbrProgram, "camPos"), 1, &cameraPosition[0]);

        // bind pre-computed IBL data
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, brdfLUTTexture);

        // rusted iron
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, ironAlbedoMap);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, ironNormalMap);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, ironMetallicMap);
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_2D, ironRoughnessMap);
        glActiveTexture(GL_TEXTURE7);
        glBindTexture(GL_TEXTURE_2D, ironAOMap);

        model = glm::mat4(1.0f);
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
		glUniformMatrix4fv(glGetUniformLocation(pbrProgram, "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix3fv(glGetUniformLocation(pbrProgram, "normalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);
        Utils::renderSphere();

        // render light source (simply re-render sphere at light positions)
        // this looks a bit off as we use the same shader, but it'll make their positions obvious and 
        // keeps the codeprint small.
        unsigned int size = sizeof(lightPositions) / sizeof(lightPositions[0]);
        for (unsigned int i = 0; i < size; ++i)
        {
            glm::vec3 newPos = lightPositions[i] + glm::vec3(sin((i / static_cast<float>(size)) * 5.0) * 5.0, 0.0, 0.0);
            newPos = lightPositions[i];
			glUniform3fv(glGetUniformLocation(pbrProgram, ("lightPositions[" + std::to_string(i) + "]").c_str()), 1, &newPos[0]);
			glUniform3fv(glGetUniformLocation(pbrProgram, ("lightColors[" + std::to_string(i) + "]").c_str()), 1, &lightColors[i][0]);

            model = glm::mat4(1.0f);
            model = glm::translate(model, newPos);
            model = glm::scale(model, glm::vec3(0.5f));
			glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
			glUniformMatrix4fv(glGetUniformLocation(pbrProgram, "model"), 1, GL_FALSE, &model[0][0]);
            glUniform3fv(glGetUniformLocation(pbrProgram, "normalMatrix"), 1, &normalMatrix[0][0]);
            Utils::renderSphere();
        }

        // render skybox (render as last to prevent overdraw)
		renderSkybox(projection, view);

		SDL_GL_SwapWindow(window);

		SDL_Delay(5000);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
