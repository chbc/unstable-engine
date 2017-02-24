#ifndef _AGRAPHICS_WRAPPER_H_
#define _AGRAPHICS_WRAPPER_H_

#include <memory>
#include <stack>
#include <string>

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
	virtual void createVBO(MeshComponent *mesh) =0;
	virtual void createIBO(MeshComponent *mesh) =0;

	virtual void bindVBO(uint32_t vbo) =0;
	virtual void enableVertexPositions() =0;
	virtual void enableVertexNormals() =0;
	virtual void enableTexCoords() =0;
	virtual void enableVertexTangents() =0;
	virtual void enableVertexBitangents() =0;
	virtual void activeDiffuseTexture(uint32_t textureId) =0;
	virtual void activeNormalTexture(uint32_t textureId) =0;
	virtual void activeSpecularTexture(uint32_t textureId) =0;
	virtual void activeAOTexture(uint32_t textureId) =0;
	virtual void drawMesh(uint32_t ibo, int indicesSize) =0;
	virtual void unbindVBO() =0;
	virtual void disableVertexPositions() =0;
	virtual void disableVertexNormals() =0;
	virtual void disableTexCoords() =0;
	virtual void disableVertexTangents() =0;
	virtual void disableVertexBitangents() =0;

	virtual void clearBuffer() =0;
	virtual uint32_t setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void *data, uint32_t unit) =0;
	virtual void deleteTexture(uint32_t id) =0;

	// Shaders
	virtual uint32_t loadVertexShader(const std::string &vertexContent) =0;
	virtual uint32_t loadFragmentShader(const std::string &vertexContent) =0;
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
friend class TextureManager;
friend class ColorRenderer;
friend class DiffuseTexturedRenderer;
friend class NormalMapRenderer;
friend class SpecularMapRenderer;
friend class AOMapRenderer;

friend class Renderer;
friend class ColorRendererComponent;
friend class DiffuseRendererComponent;
};

} // namespace
#endif
