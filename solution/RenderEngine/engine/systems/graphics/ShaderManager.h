#ifndef _GLSL_SHADER_API_H_
#define _GLSL_SHADER_API_H_

#include <string>
#include <engine/util/singleton_macros.h>
#include <stack>

namespace graphics
{

enum EShaderVariable
{
    SHADER_POSITION,
    SHADER_NORMAL
};

/*!
	Class to deal with GLSL API
*/
class ShaderManager
{
	DECLARE_SINGLETON(ShaderManager);

	private:
		std::stack<unsigned int> vertShaders;
		std::stack<unsigned int> fragShaders;
		std::stack<unsigned int> programs;

		bool loadFile(std::string fileName, std::string &dest);
		unsigned int compileShader(const std::string &fileName, const std::string &source, unsigned int mode);

		// main load function
		unsigned int loadShader(std::string vertexName, std::string fragmentName);

		// passing values //
		void setValue(unsigned int program, const std::string &varName, float x);
		void setValue(unsigned int program, const std::string &varName, float x, float y);
		void setValue(unsigned int program, const std::string &varName, float x, float y, float z);
		void setValue(unsigned int program, const std::string &varName, float *matrix);

		void setValue(unsigned int program, const std::string &varName, int value);
		void checkVariableLocation(int location, const std::string &varName);

		int getAttribLocation(unsigned int program, EShaderVariable shaderVariable);

		void enableShader(unsigned int program);
		void disableShader();

	friend class RenderManager;
	friend class LightManager;
};

} // namespace graphics

#endif
