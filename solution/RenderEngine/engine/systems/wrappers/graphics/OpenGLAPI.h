#ifndef _OPENGL_API_H_
#define _OPENGL_API_H_

#include "AGraphicsWrapper.h"

namespace sre
{

class OpenGLAPI : public AGraphicsWrapper
{
protected:
	OpenGLAPI() {}

	void init() override;
	void createVAO(MeshComponent *mesh) override {}
	void createVBO(MeshComponent *mesh) override;
	void createIBO(MeshComponent *mesh) override;
	void clearBuffer() override;
	void drawMesh(MeshComponent *mesh) override;
	void deleteTexture(uint32_t id) override;

	static void DEBUG_drawTriangle();

	// Shaders
	uint32_t loadVertexShader(const std::string &vertexFile) override;  // throws "file can't be found"
	uint32_t loadFragmentShader(const std::string &fragmentFile) override;  // throws "file can't be found"
	uint32_t createProgram(uint32_t vertexShader, int unsigned fragmentShader) override;

	void setValue(uint32_t program, const std::string &varName, float x) override;
	void setValue(uint32_t program, const std::string &varName, float x, float y) override;
	void setValue(uint32_t program, const std::string &varName, float x, float y, float z) override;
	void setValue(uint32_t program, const std::string &varName, float x, float y, float z, float w) override;
	void setValue(uint32_t program, const std::string &varName, float *matrix) override;
	void setValue(uint32_t program, const std::string &varName, int value) override;

	// ### int getAttribLocation(uint32_t program, EShaderVariable::Type shaderVariable) override;
	void enableShader(uint32_t program) override;
	void disableShader() override;
	void releaseShaders(std::stack<uint32_t> &vertShaders, std::stack<uint32_t> &fragShaders, std::stack<uint32_t> &programs) override;

private:
	uint32_t loadShader(const std::string &fileName, int shaderType);
	uint32_t compileShader(const std::string &fileName, const std::string &source, uint32_t mode);
	void checkVariableLocation(int location, const std::string &varName); // throws "invalid variable"

friend class RenderManager;
friend class ColorRenderer; // ###
};

} // namespace
#endif
