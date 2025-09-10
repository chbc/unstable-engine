#pragma once

#include "ASingleton.h"
#include "memory_aliases.h"
#include "ShaderContentFactory.h"
#include "Shader.h"
#include "ShaderLightData.h"

#include <bitset>
#include <unordered_map>

namespace sre
{

class AGraphicsWrapper;

class ShaderManager : ASingleton
{
protected:
	void init() override;
    void release() override;

private:
    std::unordered_map<uint32_t, UPTR<Shader>> shaders; // <program, shader>

    AGraphicsWrapper *graphicsWrapper;

    // main load function
    template <size_t SIZE> 
    uint32_t loadShader(
		const std::bitset<SIZE> &componentsBitset, 
		const ShaderLightData &lightData, 
		bool includeBrightnessSegmentation,
        bool includeDepth
	)
    {
        std::string vertexContent;
        std::string fragmentContent;

        ShaderContentFactory contentFactory;
        contentFactory.createShaderContent(
			componentsBitset, vertexContent, fragmentContent, lightData, 
            includeBrightnessSegmentation, includeDepth
		);

        return this->loadShader(vertexContent, fragmentContent);
    }

    uint32_t loadGUIShader();
    uint32_t loadColorShader();
    uint32_t loadCustomShader(const std::string& shaderPath);
    uint32_t loadPointLightDepthShader();
    uint32_t loadDirectionalLightDepthShader();
	uint32_t loadPostProcessingShader(class PostProcessingComponent* component);
	uint32_t loadFinalPassPostProcessingShader(class PostProcessingComponent* component);
    uint32_t loadShader(const std::string &vertexContent, const std::string &fragmentContent, const std::string& geometryContent = "");

    // passing values //
    void setupUniformLocation(uint32_t program, ShaderVariables::Type variableKey);
    void setupUniformLocation(uint32_t program, const char *variable);

    void setupAttributeLocation(uint32_t program, ShaderVariables::Type variableKey);
    void disableVertexAttribute(uint32_t program, ShaderVariables::Type variableKey);

    void setInt(uint32_t program, ShaderVariables::Type variableKey, int value);
    void setInt(uint32_t program, const char *variable, int value);
    void setFloat(uint32_t program, ShaderVariables::Type variableKey, float value);
    void setFloat(uint32_t program, const char *variable, float value);
    void setVec2(uint32_t program, ShaderVariables::Type variableKey, const float* value);
    void setVec2(uint32_t program, const char* variable, const float* value);
    void setVec3(uint32_t program, ShaderVariables::Type variableKey, const float *value);
    void setVec3(uint32_t program, const char *variable, const float *value);
    void setVec4(uint32_t program, ShaderVariables::Type variableKey, const float *value);
    void setMat4(uint32_t program, ShaderVariables::Type variableKey, const float *value);
    void setMat4(uint32_t program, const char *variable, const float *value);

    void enableShader(uint32_t program);
    void disableShader();
    void releaseShader(uint32_t program);

friend class RenderManager;
friend class LightManager;
friend class SingletonsManager;

friend class MeshRenderer;
friend class GUIRenderer;
friend class DebugRenderer;
friend class GuizmoRenderer;
friend class CustomRenderer;
friend class ColorRendererComponent;
friend class DiffuseRendererComponent;
friend class NormalRendererComponent;
friend class SpecularRendererComponent;
friend class AORendererComponent;
friend class OutlineRendererComponent;
friend class SpriteRendererComponent;
friend class PBRRendererComponent;

friend class LitRendererLightsState;

friend class BaseRendererShaderSetup;
friend class LightRendererShaderSetup;
friend class ShadowRendererShaderSetup;
friend class ShadowRenderer;
friend class PostProcessingRenderer;

friend class BloomRendererComponent;
friend class SinglePassRendererComponent;
friend class HDRRendererComponent;
friend class DOFRendererComponent;
friend class OutlineRendererPPComponent;
};

} // namespace
