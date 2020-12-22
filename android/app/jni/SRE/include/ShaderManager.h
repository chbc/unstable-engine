#ifndef _GLSL_SHADER_API_H_
#define _GLSL_SHADER_API_H_

#include <bitset>

#include "ASingleton.h"
#include "memory_aliases.h"
#include "ShaderContentFactory.h"
#include "Shader.h"
#include "ShaderLightData.h"

namespace sre
{

class AGraphicsWrapper;

/*!
	Class to deal with GLSL API
*/
class ShaderManager : ASingleton
{
protected:
	void init() override;
    void release() override;

private:
    VECTOR_UPTR<Shader> shaders;

    AGraphicsWrapper *graphicsWrapper;

    // main load function
    template <size_t SIZE> 
    Shader *loadShader(
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

    Shader* loadGUIShader();
    Shader* loadPointLightDepthShader();
    Shader* loadDirectionalLightDepthShader();
	Shader* loadPostProcessingShader(class PostProcessingComponent* component);
	Shader* loadFinalPassPostProcessingShader(class PostProcessingComponent* component);
    Shader* loadShader(const std::string &vertexContent, const std::string &fragmentContent);

    // passing values //
    void setupUniformLocation(Shader *shader, ShaderVariables::Type variableKey);
    void setupUniformLocation(Shader *shader, const char *variable);

    void setInt(Shader *shader, ShaderVariables::Type variableKey, int value);
    void setInt(Shader *shader, const char *variable, int value);
    void setFloat(Shader *shader, ShaderVariables::Type variableKey, float value);
    void setFloat(Shader *shader, const char *variable, float value);
    void setVec2(Shader* shader, const char* variable, const float* value);
    void setVec3(Shader *shader, ShaderVariables::Type variableKey, const float *value);
    void setVec3(Shader *shader, const char *variable, const float *value);
    void setVec4(Shader *shader, ShaderVariables::Type variableKey, const float *value);
    void setMat4(Shader *shader, ShaderVariables::Type variableKey, const float *value);
    void setMat4(Shader *shader, const char *variable, const float *value);

    void enableShader(Shader *shader);
    void disableShader();

friend class RenderManager;
friend class LightManager;
friend class SingletonsManager;

friend class MeshRenderer;
friend class GUIRenderer;
friend class ColorRendererComponent;
friend class DiffuseRendererComponent;
friend class NormalRendererComponent;
friend class SpecularRendererComponent;
friend class AORendererComponent;
friend class OutlineRendererComponent;
friend class SpriteRendererComponent;

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

#endif
