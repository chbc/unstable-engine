#pragma once

#include "ASingleton.h"
#include "EDrawMode.h"

#include <vector>
#include <string>

namespace sre
{

struct VertexData2D;
struct AMeshData;
struct MeshData;
struct MeshData2D;
struct ColorMeshData;

class AGraphicsWrapper : ASingleton
{
protected:
    AGraphicsWrapper() {}

public:
    virtual void createUniformBuffer(uint32_t& id, size_t size, const void* data) = 0;
	virtual void updateUniformBuffer(uint32_t id, size_t size, const void* data) = 0;
    virtual void deleteUniformBuffer(uint32_t id) = 0;
	virtual void enableBackfaceCulling(bool enable) = 0;

protected:
    virtual void createBuffers(MeshData* meshData) = 0;
    virtual void createBuffers(MeshData2D* meshData, uint32_t maxItems, bool isDynamic) = 0;
    virtual void createBuffers(ColorMeshData* meshData) = 0;
    virtual void bindVAO(uint32_t vao, uint32_t vbo) =0;

    // XXX APAGAR
    virtual void enableGUISettings() =0;
    virtual void enableColorMeshSettings() = 0;
	virtual void enablePostProcessingSettings() = 0;
    virtual void enableVertexPositions() =0;
    virtual void enableVertexNormals() =0;
    virtual void enableTexCoords() =0;
    virtual void enableVertexTangents() =0;
    virtual void enableVertexBitangents() =0;
    virtual void activateGUITexture(uint32_t textureId) =0;
    virtual void activateDiffuseTexture(uint32_t textureId) =0;
    virtual void activateNormalTexture(uint32_t textureId) =0;
    virtual void activateSpecularTexture(uint32_t textureId) =0;
    virtual void activateAOTexture(uint32_t textureId) =0;
	virtual void activateMetallicTexture(uint32_t textureId) = 0;
	virtual void activateRoughnessTexture(uint32_t textureId) = 0;

    virtual void setupBufferSubData(MeshData2D* meshData) =0;

    virtual void drawElement(uint32_t indicesId, size_t indicesSize, EDrawMode::Type drawMode = EDrawMode::TRIANGLES) = 0;

    virtual void disableVertexAttribute(int location) = 0;
    virtual void enableDepthTest() = 0;
    virtual void disableDepthTest() = 0;

    // XXX APAGAR
    virtual void disableVertexPositions() =0;
    virtual void disableVertexNormals() =0;
    virtual void disableTexCoords() =0;
    virtual void disableVertexTangents() =0;
    virtual void disableVertexBitangents() =0;
    virtual void disableGUISettings() =0;
    virtual void disableColorMeshSettings() = 0;
	virtual void disablePostProcessingSettings() =0;

	virtual void clearColorBuffer() =0;
    virtual void clearDepthBuffer() =0;
    virtual void clearColorAndDepthBuffer() =0;
    virtual uint32_t setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void *data, uint32_t unit, bool genMipmap) =0;
    virtual uint32_t createTexture(uint32_t width, uint32_t height, uint32_t unit) =0;
	virtual uint32_t createTexture(uint32_t width, uint32_t height) =0;
	virtual uint32_t createFloatingPointTexture(uint32_t width, uint32_t height) = 0;
    virtual uint32_t generateCubemap(uint32_t width, uint32_t height, uint32_t unit) =0;
    virtual void readFramebuffer(uint32_t width, uint32_t height, unsigned char* pixels) = 0;
    virtual void deleteTexture(uint32_t id) =0;

    // Shaders
    virtual uint32_t loadVertexShader(const std::string &vertexContent) =0;
    virtual uint32_t loadFragmentShader(const std::string &vertexContent) =0;
    virtual uint32_t loadGeometryShader(const std::string &geometryContent) =0;
    virtual uint32_t createProgram(const std::vector<uint32_t>& shaders) =0;

    virtual int getUniformLocation(uint32_t program, const std::string &varName) = 0;
    virtual int getAttributeLocation(uint32_t program, const std::string& varName) = 0;
    virtual void setInt(uint32_t program, int location, int value) =0;
    virtual void setFloat(uint32_t program, int location, float value) =0;
    virtual void setVec2(uint32_t program, int location, const float* value) = 0;
    virtual void setVec3(uint32_t program, int location, const float *value) =0;
    virtual void setVec4(uint32_t program, int location, const float *value) =0;
    virtual void setMat4(uint32_t program, int location, const float *value) =0;

    virtual void enableShader(uint32_t program) =0;
    virtual void disableShader() =0;
    virtual void releaseShader(uint32_t program, std::vector<uint32_t>& components) =0;
    virtual void deleteBuffers(AMeshData* meshData) =0;

    virtual uint32_t generateDepthFrameBuffer(uint32_t textureId, bool cubemap = false) =0;
	virtual uint32_t generateColorFrameBuffer(const std::vector<uint32_t>& textureIds, uint32_t width, uint32_t height) =0;
    virtual void bindFrameBuffer(uint32_t fbo) =0;
    virtual void unbindFrameBuffer() =0;
    virtual void deleteFrameBuffer(uint32_t fbo) =0;
    virtual void setViewport(uint32_t width, uint32_t height) =0;
    virtual void activateShadowMapTexture(uint32_t textureId, uint32_t unit, bool cubeMap = false) =0;
	virtual void setLineWidth(float width) = 0;
    virtual void setPointSize(float size) = 0;

friend class RenderManager;
friend class ShaderManager;
friend class SingletonsManager;
friend class TextureLoader;
friend class TextureCreator;
friend class ABaseMeshLoader;
friend class GuizmoLoader;

friend class ABaseRenderer;
friend class MeshRenderer;
friend class GUIRenderer;
friend class DebugRenderer;
friend class GuizmoRenderer;
friend class CustomRenderer;
friend class ShadowRenderer;
friend class PostProcessingRenderer;
friend class ColorRendererComponent;
friend class DiffuseRendererComponent;
friend class NormalRendererComponent;
friend class SpecularRendererComponent;
friend class AORendererComponent;
friend class OutlineRendererComponent;
friend class PBRRendererComponent;
friend class ShadowRendererShaderSetup;

friend class LitRendererLightsState;

friend class BloomRendererComponent;
friend class SinglePassRendererComponent;
friend class HDRRendererComponent;
friend class DOFRendererComponent;
friend class OutlineRendererPPComponent;

friend class EditorSceneViewport;
};

} // namespace
