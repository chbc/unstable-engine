#include "ShadowRenderer.h"
#include "MeshComponent.h"
#include "SingletonsManager.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "MessagesManager.h"
#include "AGraphicsWrapper.h"
#include "Entity.h"
#include "StringUtils.h"
#include "CollectionsUtils.h"

namespace sre
{

ShadowRenderer::ShadowRenderer(ShaderManager* arg_shaderManager, AGraphicsWrapper* arg_graphicsWrapper)
    : ABaseRenderer(arg_shaderManager, arg_graphicsWrapper)
{ }

void ShadowRenderer::init()
{
    SingletonsManager *singletonsManager = SingletonsManager::getInstance();
    this->lightManager = singletonsManager->get<LightManager>();

    this->setupLigths();
}

void ShadowRenderer::setupLigths()
{
    this->setupDirectionalLightShader();
    this->setupPointLightShader();
}

void ShadowRenderer::setupDirectionalLightShader()
{
    this->directionalLightDepthProgram = this->shaderManager->loadDirectionalLightDepthShader();

    this->shaderManager->setupUniformLocation(this->directionalLightDepthProgram, ShaderVariables::LIGHT_SPACE_MATRIX);
    this->shaderManager->setupUniformLocation(this->directionalLightDepthProgram, ShaderVariables::MODEL_MATRIX);
}

void ShadowRenderer::setupPointLightShader()
{
    this->pointLightDepthProgram = this->shaderManager->loadPointLightDepthShader();

    this->shaderManager->setupUniformLocation(this->pointLightDepthProgram, ShaderVariables::MODEL_MATRIX);
    this->shaderManager->setupUniformLocation(this->pointLightDepthProgram, ShaderVariables::FAR_PLANE);
    this->shaderManager->setupUniformLocation(this->pointLightDepthProgram, ShaderVariables::LIGHT_POSITION);

    std::string variable;
    for (unsigned int i = 0; i < 6; ++i)
    {
        variable = StringUtils::format(POINT_SHADOW_MATRICES_FORMAT, i);
        this->shaderManager->setupUniformLocation(this->pointLightDepthProgram, variable.c_str());
    }
}

void ShadowRenderer::render()
{
    if (!this->meshComponents.empty())
    {
        this->graphicsWrapper->clearColorAndDepthBuffer();

        this->graphicsWrapper->setViewport(1024, 1024);

        if (this->lightManager->pointLights.size() > 0)
            this->renderPointLightShadows();

        if (this->lightManager->directionalLights.size() > 0)
            this->renderDirectionalLightShadows();

        this->graphicsWrapper->unbindFrameBuffer();
    }
}

void ShadowRenderer::renderDirectionalLightShadows()
{
    this->shaderManager->enableShader(this->directionalLightDepthProgram);

    for (DirectionalLightComponent *light : this->lightManager->directionalLights)
    {
        this->graphicsWrapper->bindFrameBuffer(light->shadowData->fbo);
        this->graphicsWrapper->clearDepthBuffer();
        this->shaderManager->setMat4(this->directionalLightDepthProgram, ShaderVariables::LIGHT_SPACE_MATRIX, &light->lightSpaceMatrix[0][0]);

        for (MeshComponent *item : this->meshComponents)
        {
            TransformComponent *transform = item->getTransform();
            const glm::mat4& modelMatrix = transform->getMatrix();
            this->shaderManager->setMat4(this->directionalLightDepthProgram, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

            MeshData* mesh = item->mesh;
            this->graphicsWrapper->bindVAO(mesh->vao, mesh->vbo);

            this->graphicsWrapper->enableVertexPositions();
            this->graphicsWrapper->drawElement(mesh->ebo, mesh->indices.size());
            this->graphicsWrapper->disableVertexPositions();
        }
    }
}

void ShadowRenderer::renderPointLightShadows()
{
    this->shaderManager->enableShader(this->pointLightDepthProgram);

    char variable[32];
    for (PointLightComponent *light : this->lightManager->pointLights)
    {
        this->graphicsWrapper->bindFrameBuffer(light->shadowData->fbo);
        this->graphicsWrapper->clearDepthBuffer();

        const glm::vec3& lightPosition = light->getTransform()->getPosition();
        this->updateShadowMatrices(lightPosition, light->getRange());

        for (unsigned int i = 0; i < 6; ++i)
        {
			std::sprintf(variable, POINT_SHADOW_MATRICES_FORMAT, i);
            this->shaderManager->setMat4(this->pointLightDepthProgram, variable, &this->shadowMatrices[i][0][0]);
        }

        this->shaderManager->setFloat(this->pointLightDepthProgram, ShaderVariables::FAR_PLANE, light->getRange());
        this->shaderManager->setVec3(this->pointLightDepthProgram, ShaderVariables::LIGHT_POSITION, &lightPosition[0]);

        for (MeshComponent *item : this->meshComponents)
        {
            TransformComponent *transform = item->getTransform();
            glm::mat4 modelMatrix = transform->getMatrix();
            this->shaderManager->setMat4(this->pointLightDepthProgram, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

            MeshData* mesh = item->mesh;
            this->graphicsWrapper->bindVAO(mesh->vao, mesh->vbo);

            this->graphicsWrapper->enableVertexPositions();
            this->graphicsWrapper->drawElement(mesh->ebo, mesh->indices.size());
            this->graphicsWrapper->disableVertexPositions();
        }
    }
}

void ShadowRenderer::updateShadowMatrices(const glm::vec3 &lightPosition, float range)
{
    float aspect = 1.0; // 1024.0f / 1024.0f;
    float near = 0.1f;
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, near, range);

    this->shadowMatrices[0] = glm::mat4(projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    this->shadowMatrices[1] = glm::mat4(projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    this->shadowMatrices[2] = glm::mat4(projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    this->shadowMatrices[3] = glm::mat4(projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
    this->shadowMatrices[4] = glm::mat4(projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    this->shadowMatrices[5] = glm::mat4(projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
}

} // namespace
