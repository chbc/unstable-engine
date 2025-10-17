#pragma once

#ifndef __ANDROID__

#include "AGraphicsWrapper.h"
#include "ColorMeshData.h"

namespace sre
{

class OpenGLAPI : public AGraphicsWrapper
{
public:
    void createUniformBuffer(uint32_t& id, size_t size, const void* data) override;
	void updateUniformBuffer(uint32_t id, size_t size, const void* data) override;
    void deleteUniformBuffer(uint32_t id) override;
    void enableBackfaceCulling(bool enable) override;

protected:
    void init() override;
    void createBuffers(MeshData* meshData) override;
    void createBuffers(MeshData2D* meshData, uint32_t maxItems, bool isDynamic) override;
    void createBuffers(ColorMeshData* meshData) override;
    void createVAO(MeshData* meshData);
    void createEBO(MeshData* meshData);
    void createVAO(ColorMeshData* meshData);
    void createEBO(ColorMeshData* meshData);
    void createVAO(MeshData2D* meshData, uint32_t maxItems, bool isDynamic);
    void createEBO(MeshData2D* meshData, uint32_t maxItems, bool isDynamic);

    void bindVAO(uint32_t vao, uint32_t vbo) override;
    void enableColorMeshSettings() override;
    void enableGUISettings() override;
	void enablePostProcessingSettings() override;
    void enableVertexPositions() override;
    void enableVertexNormals() override;
    void enableTexCoords() override;
    void enableVertexTangents() override;
    void enableVertexBitangents() override;
    void activateTexture(uint32_t textureId, uint32_t unit) override;
    void activateCubeMapTexture(uint32_t textureId, uint32_t unit) override;
    void activateGUITexture(uint32_t textureId) override;
    void activateDiffuseTexture(uint32_t textureId) override;
    void activateNormalTexture(uint32_t textureId) override;
    void activateSpecularTexture(uint32_t textureId) override;
    void activateAOTexture(uint32_t textureId) override;
    void activateMetallicTexture(uint32_t textureId) override;
    void activateRoughnessTexture(uint32_t textureId) override;

    void setupBufferSubData(MeshData2D* meshData) override;

    void drawElement(uint32_t indicesId, size_t indicesSize, EDrawMode::Type drawMode = EDrawMode::TRIANGLES) override;

    void disableVertexAttribute(int location) override;
    void enableDepthTest() override;
    void disableDepthTest() override;

    void disableVertexPositions() override;
    void disableVertexNormals() override;
    void disableTexCoords() override;
    void disableVertexTangents() override;
    void disableVertexBitangents() override;
    void disableGUISettings() override;
    void disableColorMeshSettings() override;
	void disablePostProcessingSettings() override;

	void clearColorBuffer() override;
	void clearDepthBuffer() override;
	void clearColorAndDepthBuffer() override;
	uint32_t setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void* data, uint32_t unit, bool genMipmap = true) override;
    uint32_t setupFloatingPointTexture(int width, int height, float* data, bool genMipmap) override;
    uint32_t setupHdrBase(int faceSize) override;
    uint32_t setupHdrFromCrossedImage(int width, int height, float* data, uint32_t faceSize, bool genMipmap) override;
    uint32_t setupHdrFromEquirectangularImage(int width, int height, uint32_t sourceTextureId, uint32_t faceSize, MeshData* mesh, uint32_t program, bool genMipmap) override;
    uint32_t createTexture(uint32_t width, uint32_t height, uint32_t unit) override;
	uint32_t createTexture(uint32_t width, uint32_t height) override;
	uint32_t createFloatingPointTexture(uint32_t width, uint32_t height) override;
    uint32_t setupDepthCubemap(uint32_t width, uint32_t height, uint32_t unit) override;
    void readFramebuffer(uint32_t width, uint32_t height, unsigned char* pixels) override;
    void deleteTexture(uint32_t id) override;

    static void DEBUG_drawTriangle();

    // Shaders
    uint32_t loadVertexShader(const std::string &vertexContent) override;  // throws "file can't be found"
    uint32_t loadFragmentShader(const std::string &fragmentContent) override;  // throws "file can't be found"
    uint32_t loadGeometryShader(const std::string &geometryContent) override; // throws "file can't be found"

    uint32_t createProgram(const std::vector<uint32_t>& shaders) override;

    int getUniformLocation(uint32_t program, const std::string &varName) override;
    int getAttributeLocation(uint32_t program, const std::string& varName) override;
    void setInt(uint32_t program, int location, int value) override;
    void setFloat(uint32_t program, int location, float value) override;
    void setVec2(uint32_t program, int location, const float* value) override;
    void setVec3(uint32_t program, int location, const float *value) override;
    void setVec4(uint32_t program, int location, const float *value) override;
    void setMat3(uint32_t program, int location, const float* value) override;
    void setMat4(uint32_t program, int location, const float *value) override;

    void enableShader(uint32_t program) override;
    void disableShader() override;
    void releaseShader(uint32_t program, std::vector<uint32_t>& components) override;
    void deleteBuffers(AMeshData* mesh) override;

    uint32_t generateDepthFrameBuffer(uint32_t textureId, bool cubemap = false) override;
	uint32_t generateColorFrameBuffer(const std::vector<uint32_t>& textureIds, uint32_t width, uint32_t height) override;
    void bindFrameBuffer(uint32_t fbo) override;
    void unbindFrameBuffer() override;
    void deleteFrameBuffer(uint32_t fbo) override;
    void setViewport(uint32_t width, uint32_t height) override;
    void setLineWidth(float width) override;
    void setPointSize(float size) override;

private:
    uint32_t compileShader(const std::string &source, uint32_t mode);
    void checkVariableLocation(int location, const std::string &varName); // throws "invalid variable"
    void checkProgramLink(uint32_t program);	// throws "link error"
    static void DEBUG_renderQuad();

friend class RenderManager;
friend class SingletonsManager;
};

} // namespace
#endif
