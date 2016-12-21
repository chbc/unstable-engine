#ifndef _AGRAPHICS_WRAPPER_H_
#define _AGRAPHICS_WRAPPER_H_

#include <memory>
#include <stack>
#include <string>
#include <engine/utils/EShaderVariable.h>

namespace sre
{

class MeshComponent;

/* ###
class TextureManager;
*/

class AGraphicsWrapper
{
protected:
	AGraphicsWrapper() {}

	virtual void init() = 0; // throws std::string
	virtual void createVAO(MeshComponent *mesh) =0;
	virtual void createVBO(MeshComponent *mesh) =0;
	virtual void createIBO(MeshComponent *mesh) =0;
	virtual void drawMesh(MeshComponent *mesh) =0;
	virtual void clearBuffer() =0;
	virtual void deleteTexture(uint32_t id) =0;

	// Shaders
	virtual uint32_t loadVertexShader(const std::string &vertexFile) =0;
	virtual uint32_t loadFragmentShader(const std::string &fragmentFile) =0;
	virtual uint32_t createProgram(uint32_t vertexShader, uint32_t fragmentShader) =0;

	virtual void setValue(uint32_t program, const std::string &varName, float x) =0;
	virtual void setValue(uint32_t program, const std::string &varName, float x, float y) =0;
	virtual void setValue(uint32_t program, const std::string &varName, float x, float y, float z) =0;
	virtual void setValue(uint32_t program, const std::string &varName, float x, float y, float z, float w) =0;
	virtual void setValue(uint32_t program, const std::string &varName, float *matrix) =0;
	virtual void setValue(uint32_t program, const std::string &varName, int value) =0;

	// ### virtual int getAttribLocation(uint32_t program, EShaderVariable::Type shaderVariable) =0;
	virtual void enableShader(uint32_t program) =0;
	virtual void disableShader() =0;
	virtual void releaseShaders(std::stack<uint32_t> &vertShaders, std::stack<uint32_t> &fragShaders, std::stack<uint32_t> &programs) =0;

friend class RenderManager;
friend class ShaderManager;

/* ###
friend class TextureManager;
*/
};

} // namespace
#endif
