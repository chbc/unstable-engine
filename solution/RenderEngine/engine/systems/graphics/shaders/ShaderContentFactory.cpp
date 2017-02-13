#include "ShaderContentFactory.h"
#include <engine/utils/FileUtils.h>
#include "ShaderFiles.h"

namespace sre
{

void ShaderContentFactory::createColorContent(std::string &outVertexContent, std::string &outFragmentContent)
{
	loadColorContent(outVertexContent, outFragmentContent);

	outVertexContent = "#version 400\n" + outVertexContent;
	outFragmentContent = "#version 400\n" + outFragmentContent;
}

void ShaderContentFactory::createDiffuseContent(std::string &outVertexContent, std::string &outFragmentContent)
{
	loadDiffuseContent(outVertexContent, outFragmentContent);

	outVertexContent = "#version 400\n" + outVertexContent;
	this->replaceCode(outVertexContent, "Diffuse_setup();\n}");

	outFragmentContent = "#version 400\n" + outFragmentContent;
	this->replaceCode(outFragmentContent, "out_color = Diffuse_computeTextureColor(ka, kd, ks);\n}");
}

void ShaderContentFactory::createNormalMapContent(std::string &outVertexContent, std::string &outFragmentContent)
{
	this->loadNormalMapContent(outVertexContent, outFragmentContent);

	outVertexContent = "#version 400\n" + outVertexContent;
	this->replaceCode
	(
		outVertexContent, 
		"Diffuse_setup();\n"
		"Normal_setup();\n}"
	);

	outFragmentContent = "#version 400\n" + outFragmentContent;
	this->replaceCode
	(
		outFragmentContent, 
		"out_color = Diffuse_computeTextureColor(ka, kd, ks);\n"
		"### NORMAL_MAP\n}"
	);
}

// Load methods
void ShaderContentFactory::loadColorContent(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string mainVertex;
	std::string lightsVertex;
	std::string mainFragment;
	std::string lightsFragment;

	FileUtils::loadFile(ShaderFiles::LIGHTS_V, lightsVertex);
	FileUtils::loadFile(ShaderFiles::MAIN_V, mainVertex);
	FileUtils::loadFile(ShaderFiles::LIGHTS_F, lightsFragment);
	FileUtils::loadFile(ShaderFiles::MAIN_F, mainFragment);

	outVertexContent = lightsVertex + mainVertex;
	outFragmentContent = lightsFragment + mainFragment;
}

void ShaderContentFactory::loadDiffuseContent(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string diffuseVertex;
	std::string diffuseFragment;

	FileUtils::loadFile(ShaderFiles::DIFFUSE_V, diffuseVertex);
	FileUtils::loadFile(ShaderFiles::DIFFUSE_F, diffuseFragment);

	loadColorContent(outVertexContent, outFragmentContent);

	outVertexContent = diffuseVertex + outVertexContent;
	outFragmentContent = diffuseFragment + outFragmentContent;
}

void ShaderContentFactory::loadNormalMapContent(std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string normalVertex;
	std::string normalFragment;

	FileUtils::loadFile(ShaderFiles::NORMAL_V, normalVertex);
	FileUtils::loadFile(ShaderFiles::NORMAL_F, normalFragment);

	loadDiffuseContent(outVertexContent, outFragmentContent);

	outVertexContent = normalVertex + outVertexContent;
	outFragmentContent = normalFragment + outFragmentContent;
}

void ShaderContentFactory::replaceCode(std::string &outShaderContent, const char *code)
{
	std::size_t beginCodePosition = outShaderContent.find("// ###");
	std::size_t size = outShaderContent.size() - beginCodePosition;
	if (beginCodePosition != std::string::npos)
	{
		outShaderContent = outShaderContent.replace
		(
			beginCodePosition, size,
			code
		);
	}
	else
		throw "[ShaderContentFactory] - Didn't find code mark!";
}

} // namespace
