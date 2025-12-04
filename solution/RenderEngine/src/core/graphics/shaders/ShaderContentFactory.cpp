#include "ShaderContentFactory.h"
#include "FileUtils.h"
#include "StringUtils.h"
#include "ShaderConstants.h"
#include "PostProcessingComponent.h"

namespace sre
{

void ShaderContentFactory::createGUIShaderContent(std::string &outVertexContent, std::string &outFragmentContent)
{
    FileUtils::loadContentFile(ShaderFiles::GUI_V, outVertexContent);
    FileUtils::loadContentFile(ShaderFiles::GUI_F, outFragmentContent);
}

void ShaderContentFactory::createColorShaderContent(std::string& outVertexContent, std::string& outFragmentContent)
{
    FileUtils::loadContentFile(ShaderFiles::COLOR_V, outVertexContent);
    FileUtils::loadContentFile(ShaderFiles::COLOR_F, outFragmentContent);
}

void ShaderContentFactory::createPointLightDepthShaderContent(std::string &outVertexContent, std::string &outFragmentContent, std::string &outGeometryContent)
{
    FileUtils::loadContentFile(ShaderFiles::POINT_SHADOW_DEPTH_V, outVertexContent);
    FileUtils::loadContentFile(ShaderFiles::POINT_SHADOW_DEPTH_F, outFragmentContent);
    FileUtils::loadContentFile(ShaderFiles::POINT_SHADOW_DEPTH_G, outGeometryContent);
}

void ShaderContentFactory::createDirectionalLightDepthShaderContent(std::string &outVertexContent, std::string &outFragmentContent)
{
    FileUtils::loadContentFile(ShaderFiles::DIRECTIONAL_SHADOW_DEPTH_V, outVertexContent);
    FileUtils::loadContentFile(ShaderFiles::DIRECTIONAL_SHADOW_DEPTH_F, outFragmentContent);
}

void ShaderContentFactory::createPostProcessingShaderContent(PostProcessingComponent* component, std::string& outVertexContent, std::string& outFragmentContent)
{
	std::string mainFragmentContentHeader;
	std::string mainFragmentContentImpl;

	FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_MAIN_V, outVertexContent);
	FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_MAIN_H_F, mainFragmentContentHeader);
	FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_MAIN_IMPL_F, mainFragmentContentImpl);

	std::string effectContent;

	for (const auto& item : component->effects)
	{
		effectContent.clear();
		switch (item.first)
		{
			case PPE::GRAYSCALE:
				FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_GRAYSCALE_F, effectContent);
				mainFragmentContentHeader += effectContent;
				this->includeCallCode(mainFragmentContentImpl, "Grayscale");
				break;

			case PPE::INVERSE:
				FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_INVERSE_F, effectContent);
				mainFragmentContentHeader += effectContent;
				this->includeCallCode(mainFragmentContentImpl, "Inverse");
				break;

            case PPE::BLUR:
                FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_BLUR_F, effectContent);
                mainFragmentContentHeader += effectContent;
                this->includeCallCode(mainFragmentContentImpl, "Blur");
                break;
			
			case PPE::BLOOM:
				FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_PARTIAL_BLUR_F, effectContent);
				mainFragmentContentHeader += effectContent;
				this->includeCallCode(mainFragmentContentImpl, "PartialBlur");
				break;
			
			case PPE::HDR:
				FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_HDR_F, effectContent);
				mainFragmentContentHeader += effectContent;
				this->includeCallCode(mainFragmentContentImpl, "HDR");
				break;
			
            case PPE::DOF:
                FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_DOF_F, effectContent);
                mainFragmentContentHeader += effectContent;
                this->includeCallCode(mainFragmentContentImpl, "DOF");
                break;

            case PPE::OUTLINE:
                FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_OUTLINE_F, effectContent);
                mainFragmentContentHeader += effectContent;
                this->includeCallCode(mainFragmentContentImpl, "Outline");
                break;

			default: break;
		}
	}

	outFragmentContent = "#version 400\n" + mainFragmentContentHeader + mainFragmentContentImpl;
}

void ShaderContentFactory::createFinalPassPostProcessingShaderContent(PostProcessingComponent* component, std::string& outVertexContent, std::string& outFragmentContent)
{
	std::string mainFragmentContentHeader;
	std::string mainFragmentContentImpl;

	std::string combineFragmentContent;

	FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_MAIN_V, outVertexContent);
	FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_MAIN_H_F, mainFragmentContentHeader);
	FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_MAIN_IMPL_F, mainFragmentContentImpl);
	FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_COMBINE_F, combineFragmentContent);

	mainFragmentContentHeader = mainFragmentContentHeader + combineFragmentContent;

	this->includeCallCode(mainFragmentContentImpl, "Combine");

	/* ###
	std::string effectContent;
	std::string module;
	std::string shaderFile;

	for (const UPTR<PostProcessingEffect>& item : component->effects)
	{
		effectContent.clear();
		module.clear();
		shaderFile.clear();
		switch (item->type)
		{
		case PPE::BLUR:
			shaderFile = ShaderFiles::POST_PROCESSING_BLUR_F;
			module = "Blur";
			break;
		case PPE::GRAYSCALE:
			shaderFile = ShaderFiles::POST_PROCESSING_GRAYSCALE_F;
			module = "Grayscale";
			break;
		case PPE::INVERSE:
			shaderFile = ShaderFiles::POST_PROCESSING_INVERSE_F;
			module = "Inverse";
			break;
		case PPE::BLOOM:
			// ### shaderFile = ShaderFiles::POST_PROCESSING_BLOOM_F;
			break;
		case PPE::DEPTH_OF_FIELD: break;

		default: break;
		}

		FileUtils::loadContentFile(shaderFile, effectContent);
		mainFragmentContentHeader += effectContent;

		if (!module.empty())
			this->includeCallCode(mainFragmentContentImpl, module);
	}
	*/

	outFragmentContent = "#version 400\n" + mainFragmentContentHeader + mainFragmentContentImpl;
}

void ShaderContentFactory::loadPbrContentHeader(std::string& outVertexContent, std::string& outFragmentContent)
{
    FileUtils::loadContentFile(ShaderFiles::PBR_H_V, outVertexContent);
	FileUtils::loadContentFile(ShaderFiles::PBR_H_F, outFragmentContent);

	std::string lightUboContent;
	FileUtils::loadContentFile(ShaderFiles::LIGHTS_UBO, lightUboContent);
	outVertexContent = outVertexContent + lightUboContent;
	outFragmentContent = outFragmentContent + lightUboContent;
}

void ShaderContentFactory::loadPbrContentImplementation(std::string& outVertexContent, std::string& outFragmentContent)
{
    FileUtils::loadContentFile(ShaderFiles::PBR_IMPL_V, outVertexContent);
    FileUtils::loadContentFile(ShaderFiles::PBR_IMPL_F, outFragmentContent);
}

void ShaderContentFactory::loadCustomContent(const std::unordered_map<EShaderComponent::Type, std::string>& shaderPaths,
    std::unordered_map<EShaderComponent::Type, std::string>& outContents)
{
    for (const auto& item : shaderPaths)
    {
        std::string shaderContent;
		FileUtils::loadContentFile(item.second, shaderContent);
		outContents[item.first] = shaderContent;
	}
}

void ShaderContentFactory::loadSecondTargetColorContentImplementation(std::string& outFragmentContent)
{
    std::string content;
    FileUtils::loadContentFile(ShaderFiles::SECOND_TARGET_COLOR_F, content);

    outFragmentContent = content + outFragmentContent;
    this->uncommentCode(outFragmentContent, "// [SECOND_TARGET_COLOR]");
}

void ShaderContentFactory::loadBrightnessSegmentationContent(std::string& outFragmentContentHeader, std::string& outFragmentContentImpl)
{
	std::string fragmentContent;
	FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_BLOOM_F, fragmentContent);
	outFragmentContentHeader = outFragmentContentHeader + fragmentContent;

	this->uncommentCode(outFragmentContentImpl, "// [BLOOM]");
}

void ShaderContentFactory::loadDepthContent(std::string& outFragmentContentHeader, std::string& outFragmentContentImpl)
{
    std::string fragmentContent;
    FileUtils::loadContentFile(ShaderFiles::POST_PROCESSING_DEPTH_F, fragmentContent);
    outFragmentContentHeader = outFragmentContentHeader + fragmentContent;

    this->uncommentCode(outFragmentContentImpl, "// [DEPTH]");
}

void ShaderContentFactory::uncommentCode(std::string &outShaderContent, const std::string &mark)
{
    bool result = false;

    std::size_t position = outShaderContent.find(mark);
    while (position != std::string::npos)
    {
        result = true;
        outShaderContent = outShaderContent.erase(position, mark.size());

        position = outShaderContent.find(mark, position);
    }

    if (!result)
        throw "[ShaderContentFactory] - Didn't find code mark: " + mark;
}

void ShaderContentFactory::includeCallCode(std::string& outShaderContent, const std::string& module)
{
	std::size_t position = outShaderContent.find("// [INCLUDE]");
	if (position != std::string::npos)
	{
		std::string code = "result = " + module + "_getColor(result);\n\t";
		outShaderContent = outShaderContent.insert(position, code);
	}
	else
		throw "[ShaderContentFactory] - Didn't find code mark: [INCLUDE]";
}

} // namespace
