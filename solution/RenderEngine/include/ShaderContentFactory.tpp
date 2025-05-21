#include "EComponentId.h"

namespace sre
{

template <size_t SIZE>
void ShaderContentFactory::createShaderContent
(
    const std::bitset<SIZE> &componentsBitset, 
    std::string &outVertexContent, std::string &outFragmentContent,
    const ShaderLightData &lightData,
    bool includeBrightnessSegmentation, bool includeDepth
)
{
    this->lightData = lightData;

    std::string vertexContentHeader;
    std::string fragmentContentHeader;
    std::string vertexContentImpl;
    std::string fragmentContentImpl;

	if (componentsBitset[EComponentId::PBR_MATERIAL])
	{
		this->loadPbrContent(vertexContentImpl, fragmentContentImpl);
	}
	else
	{
        for (std::size_t i = EComponentId::COLOR_MATERIAL; i <= EComponentId::SECOND_TARGET_COLOR_MATERIAL; i++)
        {
            if (componentsBitset[i])
            {
                switch (i)
                {
                    case EComponentId::COLOR_MATERIAL:
                        this->loadColorContentHeader(vertexContentHeader, fragmentContentHeader);
                        this->loadColorContentImplementation(vertexContentImpl, fragmentContentImpl);
                        break;
                    case EComponentId::LIT_MATERIAL:
                        this->loadLightsContentHeader(vertexContentHeader, fragmentContentHeader);
                        this->loadLightsContentImplementation(vertexContentImpl, fragmentContentImpl);

                        if (this->lightData.hasAnyShadowCaster)
                        {
                            this->loadShadowsContentHeader(vertexContentHeader, fragmentContentHeader);
                            this->loadShadowsContentImplementation(vertexContentImpl, fragmentContentImpl);
                        }
                        break;
                    case EComponentId::DIFFUSE_MATERIAL:
                    case EComponentId::SPRITE_MATERIAL:
                        this->loadDiffuseContentHeader(vertexContentHeader, fragmentContentHeader);
                        this->loadDiffuseContentImplementation(vertexContentImpl, fragmentContentImpl);
                        break;
                    case EComponentId::NORMAL_MATERIAL:
                        this->loadNormalMapContentHeader(vertexContentHeader, fragmentContentHeader);
                        this->loadNormalMapContentImplementation(vertexContentImpl, fragmentContentImpl);
                        break;
                    case EComponentId::SPECULAR_MATERIAL:
                        this->loadSpecularMapContentHeader(vertexContentHeader, fragmentContentHeader);
                        this->loadSpecularMapContentImplementation(vertexContentImpl, fragmentContentImpl);
                        break;
                    case EComponentId::AO_MATERIAL:
                        this->loadAOMapContentHeader(vertexContentHeader, fragmentContentHeader);
                        this->loadAOMapContentImplementation(vertexContentImpl, fragmentContentImpl);
                        break;
                    case EComponentId::SECOND_TARGET_COLOR_MATERIAL:
                        this->loadSecondTargetColorContentImplementation(fragmentContentImpl);
                        break;
                    default: break;
                }
            }
        }
    }

	if (includeBrightnessSegmentation)
		this->loadBrightnessSegmentationContent(fragmentContentHeader, fragmentContentImpl);

    if (includeDepth)
        this->loadDepthContent(fragmentContentHeader, fragmentContentImpl);
    
#ifdef __ANDROID__
    outVertexContent = vertexContentHeader + vertexContentImpl;
    outFragmentContent = fragmentContentHeader + fragmentContentImpl;
#else
    outVertexContent = "#version 400\n" + vertexContentHeader + vertexContentImpl;
    outFragmentContent = "#version 400\n" + fragmentContentHeader + fragmentContentImpl;
#endif
}

} // namespace
