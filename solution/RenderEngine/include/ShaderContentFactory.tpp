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
        this->loadPbrContentHeader(vertexContentHeader, fragmentContentHeader);
        this->loadPbrContentImplementation(vertexContentImpl, fragmentContentImpl);
        if (this->lightData.hasAnyShadowCaster)
        {
            this->loadShadowsContentHeader(vertexContentHeader, fragmentContentHeader);
            this->loadShadowsContentImplementation(vertexContentImpl, fragmentContentImpl);
        }
	}
	else
	{
        for (std::size_t i = EComponentId::COLOR_MATERIAL; i <= EComponentId::SECOND_TARGET_COLOR_MATERIAL; i++)
        {
            if (componentsBitset[i])
            {
                switch (i)
                {
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
    outVertexContent = "#version 420\n" + vertexContentHeader + vertexContentImpl;
    outFragmentContent = "#version 420\n" + fragmentContentHeader + fragmentContentImpl;
#endif
}

} // namespace
