#ifndef _AGRAPHICS_WRAPPER_H_
#define _AGRAPHICS_WRAPPER_H_

#include "ASingleton.h"
#include <vector>
#include <string>

namespace sre
{

struct GUIVertexData;
struct AMeshData;
struct MeshData;
struct GUIMeshData;

class AGraphicsWrapper : ASingleton
{
protected:
    AGraphicsWrapper() {}

    virtual void createVAO(MeshData* meshData) =0;
    virtual void createEBO(MeshData* meshData) =0;
    virtual void createGUIVAO(GUIMeshData* meshData, uint32_t maxItems, bool isDynamic) =0;
    virtual void createGUIEBO(GUIMeshData* meshData, uint32_t maxItems, bool isDynamic) =0;

    virtual void bindVAO(uint32_t vao, uint32_t vbo) =0;
    virtual void enableGUISettings() =0;
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

    virtual void setupBufferSubData(GUIMeshData* meshData) =0;

    virtual void drawElement(uint32_t indicesSize) { }
    virtual void drawElement(uint32_t indicesId, uint32_t indicesSize) { }

    virtual void disableVertexPositions() =0;
    virtual void disableVertexNormals() =0;
    virtual void disableTexCoords() =0;
    virtual void disableVertexTangents() =0;
    virtual void disableVertexBitangents() =0;
    virtual void disableGUISettings() =0;
	virtual void disablePostProcessingSettings() =0;

	virtual void clearColorBuffer() =0;
    virtual void clearDepthBuffer() =0;
    virtual void clearColorAndDepthBuffer() =0;
    virtual uint32_t setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void *data, uint32_t unit, bool genMipmap) =0;
    virtual uint32_t createTexture(uint32_t width, uint32_t height, uint32_t unit) =0;
	virtual uint32_t createTexture(uint32_t width, uint32_t height) =0;
	virtual uint32_t createFloatingPointTexture(uint32_t width, uint32_t height) = 0;
    virtual uint32_t generateCubemap(uint32_t width, uint32_t height, uint32_t unit) =0;
    virtual void deleteTexture(uint32_t id) =0;

    // Shaders
    virtual uint32_t loadVertexShader(const std::string &vertexContent) =0;
    virtual uint32_t loadFragmentShader(const std::string &vertexContent) =0;
    virtual uint32_t loadGeometryShader(const std::string &geometryContent) =0;
    virtual uint32_t createProgram(uint32_t vertexShader, uint32_t fragmentShader) =0;
    virtual uint32_t createProgram(uint32_t vertexShader, uint32_t fragmentShader, uint32_t geometryShader) =0;

    virtual int getUniformLocation(uint32_t program, const std::string &varName) = 0;
    virtual void setInt(uint32_t program, int location, int value) =0;
    virtual void setFloat(uint32_t program, int location, float value) =0;
    virtual void setVec2(uint32_t program, int location, const float* value) = 0;
    virtual void setVec3(uint32_t program, int location, const float *value) =0;
    virtual void setVec4(uint32_t program, int location, const float *value) =0;
    virtual void setMat4(uint32_t program, int location, const float *value) =0;

    virtual void enableShader(uint32_t program) =0;
    virtual void disableShader() =0;
    virtual void releaseShader(uint32_t program, std::vector<uint32_t> components) =0;
    virtual void deleteBuffers(AMeshData* meshData) =0;

    virtual uint32_t generateDepthFrameBuffer(uint32_t textureId, bool cubemap = false) =0;
	virtual uint32_t generateColorFrameBuffer(const std::vector<uint32_t>& textureIds, uint32_t width, uint32_t height) =0;
    virtual void bindFrameBuffer(uint32_t fbo) =0;
    virtual void unbindFrameBuffer() =0;
    virtual void setViewport(uint32_t width, uint32_t height) =0;
    virtual void activateShadowMapTexture(uint32_t textureId, uint32_t unit, bool cubeMap = false) =0;

friend class RenderManager;
friend class ShaderManager;
friend class TextureManager;
friend class SingletonsManager;

friend class MeshRenderer;
friend class GUIRenderer;
friend class ShadowRenderer;
friend class PostProcessingRenderer;
friend class ColorRendererComponent;
friend class DiffuseRendererComponent;
friend class NormalRendererComponent;
friend class SpecularRendererComponent;
friend class AORendererComponent;
friend class OutlineRendererComponent;
friend class ShadowRendererShaderSetup;

friend class LitRendererLightsState;

friend class BloomRendererComponent;
friend class SinglePassRendererComponent;
friend class HDRRendererComponent;
friend class DOFRendererComponent;
friend class OutlineRendererPPComponent;
};

} // namespace
#endif
