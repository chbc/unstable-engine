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
	void createVAO(MeshComponent *mesh) override;
	void createEBO(MeshComponent *mesh) override;
	void createGUIVAO(GUIImageComponent *guiComponent) override;
	void createGUIEBO(GUIImageComponent *guiComponent) override;

	void bindVAO(uint32_t vao, uint32_t vbo) override;
	void enableGUISettings() override;
	void enableVertexPositions() override;
	void enableVertexNormals() override;
	void enableTexCoords() override;
	void enableVertexTangents() override;
	void enableVertexBitangents() override;
	void activeDiffuseTexture(uint32_t textureId) override;
	void activeNormalTexture(uint32_t textureId) override;
	void activeSpecularTexture(uint32_t textureId) override;
	void activeAOTexture(uint32_t textureId) override;

	void setupBufferSubData(const MeshData<GUIVertexData> *meshData) override;

	void drawElement(uint32_t indicesSize) override;

	void disableVertexPositions() override;
	void disableVertexNormals() override;
	void disableTexCoords() override;
	void disableVertexTangents() override;
	void disableVertexBitangents() override;
	void disableGUISettings() override;

	void clearBuffer() override;
	uint32_t setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void *data, uint32_t unit, bool genMipmap = true) override;
	void deleteTexture(uint32_t id) override;

	static void DEBUG_drawTriangle();

	// Shaders
	uint32_t loadVertexShader(const std::string &vertexContent) override;  // throws "file can't be found"
	uint32_t loadFragmentShader(const std::string &fragmentContent) override;  // throws "file can't be found"

	uint32_t createProgram(uint32_t vertexShader, uint32_t fragmentShader) override;

	void setInt(uint32_t program, const std::string &varName, int value) override;
	void setFloat(uint32_t program, const std::string &varName, float value) override;
	void setVec3(uint32_t program, const std::string &varName, const float *value) override;
	void setVec4(uint32_t program, const std::string &varName, const float *value) override;
	void setMat4(uint32_t program, const std::string &varName, const float *value) override;

	void enableShader(uint32_t program) override;
	void disableShader() override;
	void releaseShaders(std::stack<uint32_t> &vertShaders, std::stack<uint32_t> &fragShaders, std::stack<uint32_t> &programs) override;
	void deleteBuffers(MeshComponent *mesh) override;

private:
	uint32_t compileShader(const std::string &source, uint32_t mode);
	void checkVariableLocation(int location, const std::string &varName); // throws "invalid variable"
	void checkProgramLink(uint32_t program);	// throws "link error"

friend class RenderManager;
friend class ColorRenderer;
friend class TextureManager;
friend class SingletonsManager;
};

} // namespace
#endif
