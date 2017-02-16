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
	void createSpecularMapContent(std::string &outVertexContent, std::string &outFragmentContent);

	void loadColorContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
	void loadColorContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);

	void loadDiffuseContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
	void loadDiffuseContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);

	void loadNormalMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
	void loadNormalMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);

	void loadSpecularMapContentHeader(std::string &outVertexContent, std::string &outFragmentContent);
	void loadSpecularMapContentImplementation(std::string &outVertexContent, std::string &outFragmentContent);

	void uncommentCode(std::string &outShaderContent, const std::string &mark); // throws "didn't find code mark

friend class ShaderManager;
};

} // namespace

#endif
