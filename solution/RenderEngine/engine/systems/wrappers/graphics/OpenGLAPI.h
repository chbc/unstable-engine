#ifndef _OPENGL_API_H_
#define _OPENGL_API_H_

#include "AGraphicsWrapper.h"

namespace sre
{

class Mesh;

class OpenGLAPI : AGraphicsWrapper
{
	protected:
		OpenGLAPI() {}

		void init() override;
		void createVBO(Mesh *mesh) override;
		void createIBO(Mesh *mesh) override;
		void clearBuffer() override;
		void drawMesh(Mesh *mesh) override;
		void deleteTexture(unsigned int id) override;

		static void DEBUG_drawTriangle();

		// Shaders
		unsigned int loadVertexShader(const std::string &vertexFile) override;  // throws "file can't be found"
		unsigned int loadFragmentShader(const std::string &fragmentFile) override;  // throws "file can't be found"
		unsigned int createProgram(unsigned int vertexShader, int unsigned fragmentShader) override;

		void setValue(unsigned int program, const std::string &varName, float x) override;
		void setValue(unsigned int program, const std::string &varName, float x, float y) override;
		void setValue(unsigned int program, const std::string &varName, float x, float y, float z) override;
		void setValue(unsigned int program, const std::string &varName, float *matrix) override;
		void setValue(unsigned int program, const std::string &varName, int value) override;

		int getAttribLocation(unsigned int program, EShaderVariable shaderVariable) override;
		void enableShader(unsigned int program) override;
		void disableShader() override;
		void releaseShaders(std::stack<unsigned int> &vertShaders, std::stack<unsigned int> &fragShaders, std::stack<unsigned int> &programs) override;

	private:
		unsigned int loadShader(const std::string &fileName, int shaderType);
		unsigned int compileShader(const std::string &fileName, const std::string &source, unsigned int mode);
		void checkVariableLocation(int location, const std::string &varName); // throws "invalid variable"
		
	friend class AGraphicsWrapper;
};

} // namespace
#endif
