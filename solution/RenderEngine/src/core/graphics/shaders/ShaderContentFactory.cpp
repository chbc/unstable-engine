#include "ShaderContentFactory.h"
#include "FileUtils.h"
#include "StringUtils.h"
#include "ShaderConstants.h"
#include "PostProcessingComponent.h"

namespace sre
{

void ShaderContentFactory::createGUIShaderContent(std::string &outVertexContent, std::string &outFragmentContent)
{
    FileUtils::loadFile(ShaderFiles::GUI_V, outVertexContent);
    FileUtils::loadFile(ShaderFiles::GUI_F, outFragmentContent);
}

void ShaderContentFactory::createPointLightDepthShaderContent(std::string &outVertexContent, std::string &outFragmentContent, std::string &outGeometryContent)
{
    FileUtils::loadFile(ShaderFiles::POINT_SHADOW_DEPTH_V, outVertexContent);
    FileUtils::loadFile(ShaderFiles::POINT_SHADOW_DEPTH_F, outFragmentContent);
    FileUtils::loadFile(ShaderFiles::POINT_SHADOW_DEPTH_G, outGeometryContent);
}

void ShaderContentFactory::createDirectionalLightDepthShaderContent(std::string &outVertexContent, std::string &outFragmentContent)
{
    FileUtils::loadFile(ShaderFiles::DIRECTIONAL_SHADOW_DEPTH_V, outVertexContent);
    FileUtils::loadFile(ShaderFiles::DIRECTIONAL_SHADOW_DEPTH_F, outFragmentContent);
}

void ShaderContentFactory::createPostProcessingShaderContent(PostProcessingComponent* component, std::string& outVertexContent, std::string& outFragmentContent)
{
	std::string mainFragmentContentHeader;
	std::string mainFragmentContentImpl;

	FileUtils::loadFile(ShaderFiles::POST_PROCESSING_MAIN_V, outVertexContent);
	FileUtils::loadFile(ShaderFiles::POST_PROCESSING_MAIN_H_F, mainFragmentContentHeader);
	FileUtils::loadFile(ShaderFiles::POST_PROCESSING_MAIN_IMPL_F, mainFragmentContentImpl);

	std::string effectContent;

	for (const auto& item : component->effects)
	{
		effectContent.clear();
		switch (item.first)
		{
			case PPE::GRAYSCALE:
				FileUtils::loadFile(ShaderFiles::POST_PROCESSING_GRAYSCALE_F, effectContent);
				mainFragmentContentHeader += effectContent;
				this->includeCallCode(mainFragmentContentImpl, "Grayscale");
				break;

			case PPE::INVERSE:
				FileUtils::loadFile(ShaderFiles::POST_PROCESSING_INVERSE_F, effectContent);
				mainFragmentContentHeader += effectContent;
				this->includeCallCode(mainFragmentContentImpl, "Inverse");
				break;

            case PPE::BLUR:
                FileUtils::loadFile(ShaderFiles::POST_PROCESSING_BLUR_F, effectContent);
                mainFragmentContentHeader += effectContent;
                this->includeCallCode(mainFragmentContentImpl, "Blur");
                break;
			
			case PPE::BLOOM:
				FileUtils::loadFile(ShaderFiles::POST_PROCESSING_PARTIAL_BLUR_F, effectContent);
				mainFragmentContentHeader += effectContent;
				this->includeCallCode(mainFragmentContentImpl, "PartialBlur");
				break;
			
			case PPE::HDR:
				FileUtils::loadFile(ShaderFiles::POST_PROCESSING_HDR_F, effectContent);
				mainFragmentContentHeader += effectContent;
				this->includeCallCode(mainFragmentContentImpl, "HDR");
				break;
			
            case PPE::DOF:
                FileUtils::loadFile(ShaderFiles::POST_PROCESSING_DOF_F, effectContent);
                mainFragmentContentHeader += effectContent;
                this->includeCallCode(mainFragmentContentImpl, "DOF");
                break;

            case PPE::OUTLINE:
                FileUtils::loadFile(ShaderFiles::POST_PROCESSING_OUTLINE_F, effectContent);
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

	FileUtils::loadFile(ShaderFiles::POST_PROCESSING_MAIN_V, outVertexContent);
	FileUtils::loadFile(ShaderFiles::POST_PROCESSING_MAIN_H_F, mainFragmentContentHeader);
	FileUtils::loadFile(ShaderFiles::POST_PROCESSING_MAIN_IMPL_F, mainFragmentContentImpl);
	FileUtils::loadFile(ShaderFiles::POST_PROCESSING_COMBINE_F, combineFragmentContent);

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

		FileUtils::loadFile(shaderFile, effectContent);
		mainFragmentContentHeader += effectContent;

		if (!module.empty())
			this->includeCallCode(mainFragmentContentImpl, module);
	}
	*/

	outFragmentContent = "#version 400\n" + mainFragmentContentHeader + mainFragmentContentImpl;
}

// Load methods
void ShaderContentFactory::loadColorContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    FileUtils::loadFile(ShaderFiles::MAIN_H_V, outVertexContent);
    FileUtils::loadFile(ShaderFiles::MAIN_H_F, outFragmentContent);
}

void ShaderContentFactory::loadColorContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    FileUtils::loadFile(ShaderFiles::MAIN_IMPL_V, outVertexContent);
    FileUtils::loadFile(ShaderFiles::MAIN_IMPL_F, outFragmentContent);
}

void ShaderContentFactory::loadDiffuseContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string diffuseFragment;
    FileUtils::loadFile(ShaderFiles::DIFFUSE_H_F, diffuseFragment);

    outFragmentContent = diffuseFragment + outFragmentContent;
}

void ShaderContentFactory::loadDiffuseContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string diffuseFragment;

    FileUtils::loadFile(ShaderFiles::DIFFUSE_IMPL_F, diffuseFragment);
    outFragmentContent = diffuseFragment + outFragmentContent;

    this->uncommentCode(outFragmentContent, "// [DIFFUSE] ");
}

void ShaderContentFactory::loadNormalMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string normalVertex;
    std::string normalFragment;

    FileUtils::loadFile(ShaderFiles::NORMAL_H_V, normalVertex);
    FileUtils::loadFile(ShaderFiles::NORMAL_H_F, normalFragment);

    if (this->lightData.directionalLightsCount > 0)
    {
        std::string directionalNormal;
        FileUtils::loadFile(ShaderFiles::NORMAL_DIRECTIONAL_H_V, directionalNormal);

        normalVertex = normalVertex + directionalNormal;
    }

    if (this->lightData.pointLightsCount > 0)
    {
        std::string pointNormal;
        FileUtils::loadFile(ShaderFiles::NORMAL_POINT_H_V, pointNormal);

        normalVertex = normalVertex + pointNormal;
    }

    outVertexContent = normalVertex + outVertexContent;
    outFragmentContent = normalFragment + outFragmentContent;
}

void ShaderContentFactory::loadNormalMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string normalVertex;
    std::string normalFragment;

    FileUtils::loadFile(ShaderFiles::NORMAL_IMPL_V, normalVertex);
    FileUtils::loadFile(ShaderFiles::NORMAL_IMPL_F, normalFragment);

    if (this->lightData.directionalLightsCount > 0)
    {
        this->uncommentCode(normalVertex, "// [DIRECTIONAL_LIGHTS]");

        std::string directionalNormal;
        FileUtils::loadFile(ShaderFiles::NORMAL_DIRECTIONAL_IMPL_V, directionalNormal);

        normalVertex = normalVertex + directionalNormal;
    }

    if (this->lightData.pointLightsCount > 0)
    {
        this->uncommentCode(normalVertex, "// [POINT_LIGHTS]");

        std::string pointNormal;
        FileUtils::loadFile(ShaderFiles::NORMAL_POINT_IMPL_V, pointNormal);

        normalVertex = normalVertex + pointNormal;
    }

    outVertexContent = normalVertex + outVertexContent;
    outFragmentContent = normalFragment + outFragmentContent;

    this->uncommentCode(outVertexContent, "// [NORMAL] ");
    this->uncommentCode(outFragmentContent, "// [NORMAL] ");
}

void ShaderContentFactory::loadSpecularMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string specularFragment;
    FileUtils::loadFile(ShaderFiles::SPECULAR_H_F, specularFragment);

    outFragmentContent = specularFragment + outFragmentContent;
}

void ShaderContentFactory::loadSpecularMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string specularFragment;
    FileUtils::loadFile(ShaderFiles::SPECULAR_IMPL_F, specularFragment);

    outFragmentContent = specularFragment + outFragmentContent;
    this->uncommentCode(outFragmentContent, "// [SPECULAR] ");
}

void ShaderContentFactory::loadAOMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string aoFragment;
    FileUtils::loadFile(ShaderFiles::AMBIENT_OCCLUSION_H_F, aoFragment);

    outFragmentContent = aoFragment + outFragmentContent;
}

void ShaderContentFactory::loadAOMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string aoFragment;

    FileUtils::loadFile(ShaderFiles::AMBIENT_OCCLUSION_IMPL_F, aoFragment);

    outFragmentContent = aoFragment + outFragmentContent;
    this->uncommentCode(outFragmentContent, "// [AO] ");
}

void ShaderContentFactory::loadSecondTargetColorContentImplementation(std::string& outFragmentContent)
{
    std::string content;
    FileUtils::loadFile(ShaderFiles::SECOND_TARGET_COLOR_F, content);

    outFragmentContent = content + outFragmentContent;
    this->uncommentCode(outFragmentContent, "// [SECOND_TARGET_COLOR]");
}

void ShaderContentFactory::loadLightsContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string vertexContent;
    std::string fragmentContent;

    FileUtils::loadFile(ShaderFiles::LIGHTS_H_V, vertexContent);
    FileUtils::loadFile(ShaderFiles::LIGHTS_H_F, fragmentContent);

    int lightsCount = this->lightData.directionalLightsCount;

    if (lightsCount > 0)
    {
        std::string directionalVertexContent;
        std::string directionalFragmentContent;
        FileUtils::loadFile(ShaderFiles::DIRECTIONAL_LIGHTS_H_V, directionalVertexContent);
        FileUtils::loadFile(ShaderFiles::DIRECTIONAL_LIGHTS_H_F, directionalFragmentContent);

        directionalVertexContent = StringUtils::format(directionalVertexContent, lightsCount);
        directionalFragmentContent = StringUtils::format(directionalFragmentContent, lightsCount);

        vertexContent += directionalVertexContent;
        fragmentContent += directionalFragmentContent;
    }

    lightsCount = this->lightData.pointLightsCount;
    if (lightsCount > 0)
    {
        std::string pointVertexContent;
        std::string pointFragmentContent;
        FileUtils::loadFile(ShaderFiles::POINT_LIGHTS_H_V, pointVertexContent);
        FileUtils::loadFile(ShaderFiles::POINT_LIGHTS_H_F, pointFragmentContent);

        pointVertexContent = StringUtils::format(pointVertexContent, lightsCount);
        pointFragmentContent = StringUtils::format(pointFragmentContent, lightsCount);

        vertexContent += pointVertexContent;
        fragmentContent += pointFragmentContent;
    }

    outVertexContent = vertexContent + outVertexContent;
    outFragmentContent = fragmentContent + outFragmentContent;
}

void ShaderContentFactory::loadLightsContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string vertexContent;
    std::string fragmentContent;

    FileUtils::loadFile(ShaderFiles::LIGHTS_IMPL_V, vertexContent);
    FileUtils::loadFile(ShaderFiles::LIGHTS_IMPL_F, fragmentContent);

    this->uncommentCode(outVertexContent, "// [LIGHTS]");
    this->uncommentCode(outFragmentContent, "// [LIGHTS]");

    if (this->lightData.directionalLightsCount > 0)
    {
        std::string directionalVertexContent;
        std::string directionalFragmentContent;
        FileUtils::loadFile(ShaderFiles::DIRECTIONAL_LIGHTS_IMPL_V, directionalVertexContent);
        FileUtils::loadFile(ShaderFiles::DIRECTIONAL_LIGHTS_IMPL_F, directionalFragmentContent);

        this->uncommentCode(vertexContent, "// [DIRECTIONAL_LIGHTS]");
        this->uncommentCode(fragmentContent, "// [DIRECTIONAL_LIGHTS]");

        vertexContent += directionalVertexContent;
        fragmentContent += directionalFragmentContent;
    }

    if (this->lightData.pointLightsCount > 0)
    {
        std::string pointVertexContent;
        std::string pointFragmentContent;
        FileUtils::loadFile(ShaderFiles::POINT_LIGHTS_IMPL_V, pointVertexContent);
        FileUtils::loadFile(ShaderFiles::POINT_LIGHTS_IMPL_F, pointFragmentContent);

        this->uncommentCode(vertexContent, "// [POINT_LIGHTS]");
        this->uncommentCode(fragmentContent, "// [POINT_LIGHTS]");

        vertexContent += pointVertexContent;
        fragmentContent += pointFragmentContent;
    }

    outVertexContent = vertexContent + outVertexContent;
    outFragmentContent = fragmentContent + outFragmentContent;
}

void ShaderContentFactory::loadShadowsContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string vertexContent;
    std::string fragmentContent;

    if (this->lightData.directionalLightsCount > 0)
    {
        std::string directionalVertex;
        std::string directionalFragment;

        FileUtils::loadFile(ShaderFiles::SHADOWS_DIRECTIONAL_H_V, directionalVertex);
        FileUtils::loadFile(ShaderFiles::SHADOWS_DIRECTIONAL_H_F, directionalFragment);

        vertexContent += directionalVertex;
        fragmentContent += directionalFragment;
    }

    if (this->lightData.pointLightsCount > 0)
    {
        std::string pointVertex;
        std::string pointFragment;

        FileUtils::loadFile(ShaderFiles::SHADOWS_POINT_H_V, pointVertex);
        FileUtils::loadFile(ShaderFiles::SHADOWS_POINT_H_F, pointFragment);

        vertexContent   += pointVertex;
        fragmentContent += pointFragment;
    }

    outVertexContent += vertexContent;
    outFragmentContent += fragmentContent;
}

void ShaderContentFactory::loadShadowsContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string vertexContent;
    std::string fragmentContent;

    if (this->lightData.directionalLightsCount > 0)
    {
        this->uncommentCode(outVertexContent, "// [DIRECTIONAL_SHADOWS]");
        this->uncommentCode(outFragmentContent, "// [DIRECTIONAL_SHADOWS]");

        std::string directionalVertex;
        std::string directionalFragment;

        FileUtils::loadFile(ShaderFiles::SHADOWS_DIRECTIONAL_IMPL_V, directionalVertex);
        FileUtils::loadFile(ShaderFiles::SHADOWS_DIRECTIONAL_IMPL_F, directionalFragment);

        vertexContent += directionalVertex;
        fragmentContent += directionalFragment;
    }

    if (this->lightData.pointLightsCount > 0)
    {
        this->uncommentCode(outVertexContent, "// [POINT_SHADOWS]");
        this->uncommentCode(outFragmentContent, "// [POINT_SHADOWS]");

        std::string pointVertex;
        std::string pointFragment;

        FileUtils::loadFile(ShaderFiles::SHADOWS_POINT_IMPL_V, pointVertex);
        FileUtils::loadFile(ShaderFiles::SHADOWS_POINT_IMPL_F, pointFragment);

        vertexContent += pointVertex;
        fragmentContent += pointFragment;
    }

    outVertexContent = vertexContent + outVertexContent;
    outFragmentContent = fragmentContent + outFragmentContent;
}

void ShaderContentFactory::loadBrightnessSegmentationContent(std::string& outFragmentContentHeader, std::string& outFragmentContentImpl)
{
	std::string fragmentContent;
	FileUtils::loadFile(ShaderFiles::POST_PROCESSING_BLOOM_F, fragmentContent);
	outFragmentContentHeader = outFragmentContentHeader + fragmentContent;

	this->uncommentCode(outFragmentContentImpl, "// [BLOOM]");
}

void ShaderContentFactory::loadDepthContent(std::string& outFragmentContentHeader, std::string& outFragmentContentImpl)
{
    std::string fragmentContent;
    FileUtils::loadFile(ShaderFiles::POST_PROCESSING_DEPTH_F, fragmentContent);
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
