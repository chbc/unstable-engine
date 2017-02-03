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
	outFragmentContent = "#version 400\n" + outFragmentContent;
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

} // namespace
