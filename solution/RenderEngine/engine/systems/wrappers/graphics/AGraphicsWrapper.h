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
	virtual void drawColorMesh(MeshComponent *mesh) =0;
	virtual void drawTexturedMesh(MeshComponent *mesh, uint32_t textureId) =0;
	virtual void clearBuffer() =0;
	virtual uint32_t setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void *data) =0;
	virtual void deleteTexture(uint32_t id) =0;

	// Shaders
	virtual uint32_t loadVertexShader(const std::string &vertexFile) =0;
	virtual uint32_t loadFragmentShader(const std::string &fragmentFile) =0;
	virtual uint32_t createProgram(uint32_t vertexShader, uint32_t fragmentShader) =0;

	virtual void setInt(uint32_t program, const std::string &varName, int value) =0;
	virtual void setFloat(uint32_t program, const std::string &varName, float value) =0;
	virtual void setVec3(uint32_t program, const std::string &varName, const float *value) =0;
	virtual void setVec4(uint32_t program, const std::string &varName, const float *value) =0;
	virtual void setMat4(uint32_t program, const std::string &varName, const float *value) =0;

	virtual void enableShader(uint32_t program) =0;
	virtual void disableShader() =0;
	virtual void releaseShaders(std::stack<uint32_t> &vertShaders, std::stack<uint32_t> &fragShaders, std::stack<uint32_t> &programs) =0;

friend class RenderManager;
friend class ShaderManager;
friend class ColorRenderer; // ###
friend class DiffuseTexturedRenderer;
friend class TextureManager;

};

} // namespace
#endif
