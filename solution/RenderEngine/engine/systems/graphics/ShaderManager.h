#ifndef _GLSL_SHADER_API_H_
#define _GLSL_SHADER_API_H_

#include <string>
#include <engine/utils/memory_aliases.h>
#include <stack>

namespace sre
{

class AGraphicsWrapper;

/*!
	Class to deal with GLSL API
*/
class ShaderManager
{
public:
	~ShaderManager();

private:
	std::stack<uint32_t> vertShaders;
	std::stack<uint32_t> fragShaders;
	std::stack<uint32_t> programs;

	SPTR<AGraphicsWrapper> graphicsWrapper;

	ShaderManager(const SPTR<AGraphicsWrapper> &graphicsWrapper);

	// main load function
	uint32_t loadColorShader();
	uint32_t loadDiffuseShader();
	uint32_t loadNormalMapShader();
	uint32_t loadSpecularMapShader();
	uint32_t loadAOMapShader();
	uint32_t loadShader(const std::string &vertexContent, const std::string &fragmentContent);

	// passing values //
	void setInt(uint32_t program, const std::string &varName, int value);
	void setFloat(uint32_t program, const std::string &varName, float value);
	void setVec3(uint32_t program, const std::string &varName, const float *value);
	void setVec4(uint32_t program, const std::string &varName, const float *value);
	void setMat4(uint32_t program, const std::string &varName, const float *value);

	void enableShader(uint32_t program);
	void disableShader();

friend class RenderManager;
friend class LightManager;
friend class ColorRenderer;
friend class DiffuseTexturedRenderer;
friend class NormalMapRenderer;
friend class SpecularMapRenderer;
friend class AOMapRenderer;
};

} // namespace

#endif
