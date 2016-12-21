#ifndef _GLSL_SHADER_API_H_
#define _GLSL_SHADER_API_H_

#include <string>
#include <engine/utils/memory_aliases.h>
#include <engine/utils/EShaderVariable.h>
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
		std::stack<unsigned int> vertShaders;
		std::stack<unsigned int> fragShaders;
		std::stack<unsigned int> programs;

		SPTR<AGraphicsWrapper> graphicsWrapper;

		ShaderManager(const SPTR<AGraphicsWrapper> &graphicsWrapper);

		// main load function
		unsigned int loadShader(const std::string &vertexName, const std::string &fragmentName);

		// passing values //
		void setValue(unsigned int program, const std::string &varName, float x);
		void setValue(unsigned int program, const std::string &varName, float x, float y);
		void setValue(unsigned int program, const std::string &varName, float x, float y, float z);
		void setValue(unsigned int program, const std::string &varName, float x, float y, float z, float w);
		void setValue(unsigned int program, const std::string &varName, float *matrix);

		void setValue(unsigned int program, const std::string &varName, int value);

		int getAttribLocation(unsigned int program, EShaderVariable::Type shaderVariable);

		void enableShader(unsigned int program);
		void disableShader();

	friend class RenderManager;
	friend class LightManager;
};

} // namespace

#endif
