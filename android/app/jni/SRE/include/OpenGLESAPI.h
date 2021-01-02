#ifdef __ANDROID__

#ifndef _OPENGL_ES_API_H_
#define _OPENGL_ES_API_H_

#include "AGraphicsWrapper.h"

namespace sre
{
    class MultimediaManager;

    class OpenGLESAPI : public AGraphicsWrapper
    {
    private:
        MultimediaManager* multimediaManager;

    protected:
        OpenGLESAPI() {}

        void init() override;
        void createVAO(MeshData* meshData) override;
        void createEBO(MeshData* meshData) override;
        void createGUIVAO(GUIMeshData* meshData, uint32_t maxItems, bool isDynamic) override;
        void createGUIEBO(GUIMeshData* meshData, uint32_t maxItems, bool isDynamic) override;

        void bindVAO(uint32_t vao, uint32_t vbo) override;
        void setVertexAttributePointer(int attributeLocation, size_t itemSize, size_t dataSize, void* dataOffset) override;
        // XXX APAGAR
        void enableGUISettings() override;
        void enablePostProcessingSettings() override;
        void enableVertexPositions() override;
        void enableVertexNormals() override;
        void enableTexCoords() override;
        void enableVertexTangents() override;
        void enableVertexBitangents() override;
        void activateGUITexture(uint32_t textureId) override;
        void activateDiffuseTexture(uint32_t textureId) override;
        void activateNormalTexture(uint32_t textureId) override;
        void activateSpecularTexture(uint32_t textureId) override;
        void activateAOTexture(uint32_t textureId) override;

        void setupBufferSubData(GUIMeshData* meshData) override;

        void drawElement(uint32_t indicesId, uint32_t indicesSize) override;

        void disableVertexAttribute(int location) override;

        // XXX APAGAR
        void disableVertexPositions() override;
        void disableVertexNormals() override;
        void disableTexCoords() override;
        void disableVertexTangents() override;
        void disableVertexBitangents() override;
        void disableGUISettings() override;
        void disablePostProcessingSettings() override;

        void clearColorBuffer() override;
        void clearDepthBuffer() override;
        void clearColorAndDepthBuffer() override;
        uint32_t setupTexture(uint32_t width, uint32_t height, uint8_t bpp, void* data, uint32_t unit, bool genMipmap) override;
        uint32_t createTexture(uint32_t width, uint32_t height, uint32_t unit) override { return 0; }
        uint32_t createTexture(uint32_t width, uint32_t height) override { return 0; }
        uint32_t createFloatingPointTexture(uint32_t width, uint32_t height) override { return 0; }
        uint32_t generateCubemap(uint32_t width, uint32_t height, uint32_t unit) override { return 0; }
        void deleteTexture(uint32_t id) override;

        // Shaders
        uint32_t loadVertexShader(const std::string& vertexContent) override;  // throws "file can't be found"
        uint32_t loadFragmentShader(const std::string& fragmentContent) override;  // throws "file can't be found"
        uint32_t loadGeometryShader(const std::string& geometryContent) override; // throws "file can't be found"
        uint32_t createProgram(uint32_t vertexShader, uint32_t fragmentShader) override;
        uint32_t createProgram(uint32_t vertexShader, uint32_t fragmentShader, uint32_t geometryShader) override;

        int getUniformLocation(uint32_t program, const std::string& varName) override;
        int getAttributeLocation(uint32_t program, const std::string& varName) override;
        void setInt(uint32_t program, int location, int value) override;
        void setFloat(uint32_t program, int location, float value) override;
        void setVec2(uint32_t program, int location, const float* value) override;
        void setVec3(uint32_t program, int location, const float* value) override;
        void setVec4(uint32_t program, int location, const float* value) override;
        void setMat4(uint32_t program, int location, const float* value) override;

        void enableShader(uint32_t program) override;
        void disableShader() override;
        void releaseShader(uint32_t program, std::vector<uint32_t> components) override;
        void deleteBuffers(AMeshData* meshData) override;

        uint32_t generateDepthFrameBuffer(uint32_t textureId, bool cubemap = false) override { return 0; }
        uint32_t generateColorFrameBuffer(const std::vector<uint32_t>& textureIds, uint32_t width, uint32_t height) override { return 0; }
        void bindFrameBuffer(uint32_t fbo) override;
        void unbindFrameBuffer() override;
        void setViewport(uint32_t width, uint32_t height) override;
        void activateShadowMapTexture(uint32_t textureId, uint32_t unit, bool cubeMap) override;

    private:
        uint32_t compileShader(const std::string& source, uint32_t mode);
        void checkVariableLocation(int location, const std::string& varName); // throws "invalid variable"
        void checkProgramLink(uint32_t program);	// throws "link error"

        friend class RenderManager;
        friend class SingletonsManager;
    };

} // namespace
#endif
#endif
