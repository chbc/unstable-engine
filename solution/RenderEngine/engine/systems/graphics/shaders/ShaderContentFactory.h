#ifndef _SHADER_CONTENT_FACTORY_H_
#define _SHADER_CONTENT_FACTORY_H_

#include <string>

namespace sre
{

class ShaderContentFactory
{
private:
	void createColorContent(std::string &outVertexContent, std::string &outFragmentContent);
	void createDiffuseContent(std::string &outVertexContent, std::string &outFragmentContent);
	void createNormalMapContent(std::string &outVertexContent, std::string &outFragmentContent);

	void loadColorContent(std::string &outVertexContent, std::string &outFragmentContent);
	void loadDiffuseContent(std::string &outVertexContent, std::string &outFragmentContent);
	void loadNormalMapContent(std::string &outVertexContent, std::string &outFragmentContent);

	void replaceCode(std::string &outShaderContent, const char *code); // throws "didn't find code mark

friend class ShaderManager;
};

} // namespace

#endif
