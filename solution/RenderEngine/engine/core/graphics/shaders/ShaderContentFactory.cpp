#include "ShaderContentFactory.h"
#include <engine/utils/FileUtils.h>
#include "ShaderConstants.h"

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

// Load methods
void ShaderContentFactory::loadColorContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string lightsVertex;
    std::string mainVertex;
    std::string lightsFragment;
    std::string mainFragment;

    FileUtils::loadFile(ShaderFiles::LIGHTS_H_V, lightsVertex);
    FileUtils::loadFile(ShaderFiles::MAIN_H_V, mainVertex);
    FileUtils::loadFile(ShaderFiles::LIGHTS_H_F, lightsFragment);
    FileUtils::loadFile(ShaderFiles::MAIN_H_F, mainFragment);

    outVertexContent = lightsVertex + mainVertex;
    outFragmentContent = lightsFragment + mainFragment;
}

void ShaderContentFactory::loadColorContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string lightsVertex;
    std::string mainVertex;
    std::string lightsFragment;
    std::string mainFragment;

    FileUtils::loadFile(ShaderFiles::LIGHTS_IMPL_V, lightsVertex);
    FileUtils::loadFile(ShaderFiles::MAIN_IMPL_V, mainVertex);
    FileUtils::loadFile(ShaderFiles::LIGHTS_IMPL_F, lightsFragment);
    FileUtils::loadFile(ShaderFiles::MAIN_IMPL_F, mainFragment);

    outVertexContent = lightsVertex + mainVertex;
    outFragmentContent = lightsFragment + mainFragment;
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

    outVertexContent = normalVertex + outVertexContent;
    outFragmentContent = normalFragment + outFragmentContent;
}

void ShaderContentFactory::loadNormalMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string normalVertex;
    std::string normalFragment;

    FileUtils::loadFile(ShaderFiles::NORMAL_IMPL_V, normalVertex);
    FileUtils::loadFile(ShaderFiles::NORMAL_IMPL_F, normalFragment);

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

void ShaderContentFactory::loadShadowsContentHeader(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string vertexContent;
    std::string fragmentContent;

    FileUtils::loadFile(ShaderFiles::SHADOWS_H_V, vertexContent);
    FileUtils::loadFile(ShaderFiles::SHADOWS_H_F, fragmentContent);

    outVertexContent = vertexContent + outVertexContent;
    outFragmentContent = fragmentContent + outFragmentContent;
}

void ShaderContentFactory::loadShadowsContentImplementation(std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string shaderContent;
    FileUtils::loadFile(ShaderFiles::SHADOWS_IMPL_F, shaderContent);

    outFragmentContent = shaderContent + outFragmentContent;
    this->uncommentCode(outVertexContent, "// [SHADOWS]");
    this->uncommentCode(outFragmentContent, "// [SHADOWS]");
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
        throw "[ShaderContentFactory] - Didn't find code mark!";
}

} // namespace
