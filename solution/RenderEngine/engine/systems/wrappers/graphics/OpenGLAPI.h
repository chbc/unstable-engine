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
	void drawMesh(MeshComponent *mesh, int vertexLocation, int normalLocation) override;
	void deleteTexture(uint32_t id) override;

	static void DEBUG_drawTriangle();

	// Shaders
	uint32_t loadVertexShader(const std::string &vertexFile) override;  // throws "file can't be found"
	uint32_t loadFragmentShader(const std::string &fragmentFile) override;  // throws "file can't be found"
	uint32_t createProgram(uint32_t vertexShader, uint32_t fragmentShader) override;

	void setInt(uint32_t program, const std::string &varName, int value) override;
	void setFloat(uint32_t program, const std::string &varName, float value) override;
	void setVec3(uint32_t program, const std::string &varName, const float *value) override;
	void setVec4(uint32_t program, const std::string &varName, const float *value) override;
	void setMat4(uint32_t program, const std::string &varName, const float *value) override;

	// ### int getAttribLocation(uint32_t program, EShaderVariable::Type shaderVariable) override;
	void enableShader(uint32_t program) override;
	void disableShader() override;
	void releaseShaders(std::stack<uint32_t> &vertShaders, std::stack<uint32_t> &fragShaders, std::stack<uint32_t> &programs) override;

private:
	uint32_t loadShader(const std::string &fileName, int shaderType);
	uint32_t compileShader(const std::string &fileName, const std::string &source, uint32_t mode);
	void checkVariableLocation(int location, const std::string &varName); // throws "invalid variable"
	void checkProgramLink(uint32_t program);	// throws "link error"

friend class RenderManager;
friend class ColorRenderer; // ###
};

} // namespace
#endif
