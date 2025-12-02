#pragma once

#include "EShaderComponent.h"

#include <unordered_map>
#include <string>
#include <bitset>

namespace sre
{

class ShaderContentFactory
{
private:
    template <size_t SIZE>
    void createShaderContent
    (
        const std::bitset<SIZE> &componentsBitset, 
        std::string &outVertexContent, std::string &outFragmentContent, 
        bool includeBrightnessSegmentation, bool includeDepth
    );
    void createGUIShaderContent(std::string &outVertexContent, std::string &outFragmentContent);
    void createColorShaderContent(std::string& outVertexContent, std::string& outFragmentContent);
    void createPointLightDepthShaderContent(std::string &outVertexContent, std::string &outFragmentContent, std::string &outGeometryContent);
    void createDirectionalLightDepthShaderContent(std::string &outVertexContent, std::string &outFragmentContent);
	void createPostProcessingShaderContent(class PostProcessingComponent* component, std::string& outVertexContent, std::string& outFragmentContent);
	void createFinalPassPostProcessingShaderContent(class PostProcessingComponent* component, std::string& outVertexContent, std::string& outFragmentContent);

    void loadPbrContentHeader(std::string& outVertexContent, std::string& outFragmentContent);
    void loadPbrContentImplementation(std::string& outVertexContent, std::string& outFragmentContent);
    void loadCustomContent(const std::unordered_map<EShaderComponent::Type, std::string>& shaderPaths, std::unordered_map<EShaderComponent::Type, std::string>& outContents);

    void loadSecondTargetColorContentImplementation(std::string& outFragmentContent);

    void loadShadowsContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
    void loadShadowsContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);
	
	void loadBrightnessSegmentationContent(std::string& outFragmentContentHeader, std::string& outFragmentContentImpl);
    void loadDepthContent(std::string& outFragmentContentHeader, std::string& outFragmentContentImpl);

    void uncommentCode(std::string &outShaderContent, const std::string &mark); // throws "didn't find code mark
	void includeCallCode(std::string& outShaderContent, const std::string& module); // throws "didn't find code mark

friend class ShaderManager;
};

} // namespace

#include "ShaderContentFactory.tpp"
