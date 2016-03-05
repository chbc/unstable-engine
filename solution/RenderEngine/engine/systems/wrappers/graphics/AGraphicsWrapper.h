#ifndef _AGRAPHICS_WRAPPER_H_
#define _AGRAPHICS_WRAPPER_H_

#include <memory>
#include <stack>
#include <string>
#include <engine/util/EShaderVariable.h>

namespace sre
{

class Mesh;
class RenderManager;
class TextureManager;
class ShaderManager;

class AGraphicsWrapper
{
	private:
		static std::unique_ptr<AGraphicsWrapper> instance;

	protected:
		AGraphicsWrapper() {}

		static AGraphicsWrapper *getInstance();

		virtual void init() = 0; // throws std::string
		virtual void createVBO(Mesh *mesh) =0;
		virtual void createIBO(Mesh *mesh) =0;
		virtual void drawMesh(Mesh *mesh) = 0;
		virtual void clearBuffer() =0;
		virtual void deleteTexture(unsigned int id) =0;

		static void DEBUG_drawTriangle();

		// Shaders
		virtual unsigned int loadVertexShader(const std::string &vertexFile) =0;
		virtual unsigned int loadFragmentShader(const std::string &fragmentFile) = 0;
		virtual unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader) = 0;

		virtual void setValue(unsigned int program, const std::string &varName, float x) =0;
		virtual void setValue(unsigned int program, const std::string &varName, float x, float y) =0;
		virtual void setValue(unsigned int program, const std::string &varName, float x, float y, float z) =0;
		virtual void setValue(unsigned int program, const std::string &varName, float *matrix) =0;
		virtual void setValue(unsigned int program, const std::string &varName, int value) =0;

		virtual int getAttribLocation(unsigned int program, EShaderVariable shaderVariable) =0;
		virtual void enableShader(unsigned int program) =0;
		virtual void disableShader() =0;
		virtual void releaseShaders(std::stack<unsigned int> &vertShaders, std::stack<unsigned int> &fragShaders, std::stack<unsigned int> &programs) =0;

	friend class RenderManager;
	friend class TextureManager;
	friend class ShaderManager;
};

} // namespace
#endif
