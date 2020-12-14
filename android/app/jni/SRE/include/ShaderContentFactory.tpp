#include "EComponentId.h"

// ### ANDROID
#include <SDL_log.h>

namespace sre
{

template <size_t SIZE>
void ShaderContentFactory::createShaderContent
(
    const std::bitset<SIZE> &componentsBitset, 
    std::string &outVertexContent, std::string &outFragmentContent,
    const ShaderLightData &lightData
)
{
    this->lightData = lightData;

    std::string vertexContentHeader;
    std::string fragmentContentHeader;
    std::string vertexContentImpl;
    std::string fragmentContentImpl;

	SDL_Log("XXX ShaderContentFactory - createShaderContent 1");

    for (std::size_t i = EComponentId::COLOR_MATERIAL; i <= EComponentId::AO_MATERIAL; i++)
    {
		SDL_Log("XXX ShaderContentFactory - createShaderContent 2");
        if (componentsBitset[i])
        {
            switch (i)
            {
                case EComponentId::COLOR_MATERIAL:
					SDL_Log("XXX ShaderContentFactory - createShaderContent | COLOR_MATERIAL");
                    this->loadColorContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadColorContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::LIT_MATERIAL:
					SDL_Log("XXX ShaderContentFactory - createShaderContent | LIT_MATERIAL");
                    this->loadLightsContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadLightsContentImplementation(vertexContentImpl, fragmentContentImpl);

                    if (this->lightData.hasAnyShadowCaster)
                    {
						SDL_Log("XXX ShaderContentFactory - createShaderContent | HAS SHADOWS");
                        this->loadShadowsContentHeader(vertexContentHeader, fragmentContentHeader);
                        this->loadShadowsContentImplementation(vertexContentImpl, fragmentContentImpl);
                    }
                    break;
                case EComponentId::DIFFUSE_MATERIAL:
					SDL_Log("XXX ShaderContentFactory - createShaderContent | DIFFUSE_MATERIAL");
                    this->loadDiffuseContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadDiffuseContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::NORMAL_MATERIAL:
                    SDL_Log("XXX ShaderContentFactory - createShaderContent | NORMAL_MATERIAL");
                    this->loadNormalMapContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadNormalMapContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::SPECULAR_MATERIAL:
                    SDL_Log("XXX ShaderContentFactory - createShaderContent | SPECULAR_MATERIAL");
                    this->loadSpecularMapContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadSpecularMapContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::AO_MATERIAL:
                    SDL_Log("XXX ShaderContentFactory - createShaderContent | AO_MATERIAL");
                    this->loadAOMapContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadAOMapContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                default: break;
            }
        }
    }

	SDL_Log("XXX ShaderContentFactory - createShaderContent 3");
    
#ifdef __ANDROID__
    outVertexContent = vertexContentHeader + vertexContentImpl;
    outFragmentContent = fragmentContentHeader + fragmentContentImpl;
#else
    outVertexContent = "#version 400\n" + vertexContentHeader + vertexContentImpl;
    outFragmentContent = "#version 400\n" + fragmentContentHeader + fragmentContentImpl;
#endif

}

} // namespace
