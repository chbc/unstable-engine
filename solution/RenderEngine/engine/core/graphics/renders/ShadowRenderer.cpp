#include "ShadowRenderer.h"

#include <engine/entities/components/renderables/meshes/MeshComponent.h>
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <engine/core/multimedia/textures/TextureManager.h>
#include <engine/core/graphics/LightManager.h>
#include <engine/core/graphics/ShaderManager.h>
#include <engine/core/wrappers/graphics/AGraphicsWrapper.h>
#include <experimental/vector>
#include <engine/entities/Entity.h>

namespace sre
{

ShadowRenderer::ShadowRenderer() {}

void ShadowRenderer::onSceneLoaded()
{
    SingletonsManager *singletonsManager = SingletonsManager::getInstance();
    this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
    this->shaderManager = singletonsManager->get<ShaderManager>();

    this->lightManager = singletonsManager->get<LightManager>();
    TextureManager *textureManager = singletonsManager->resolve<TextureManager>();

    if (this->lightManager->directionalLights.size() > 0)
        this->setupDirectionalLightShader(textureManager);

    if (this->lightManager->pointLights.size() > 0)
        this->setupPointLightShader(textureManager);
}

void ShadowRenderer::setupDirectionalLightShader(TextureManager *textureManager)
{
    this->directionalLightDepthShader = this->shaderManager->loadDirectionalLightDepthShader();

    this->shaderManager->setupUniformLocation(this->directionalLightDepthShader, ShaderVariables::LIGHT_SPACE_MATRIX);
    this->shaderManager->setupUniformLocation(this->directionalLightDepthShader, ShaderVariables::MODEL_MATRIX);

    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f);

    for (DirectionalLightComponent *item : this->lightManager->directionalLights)
    {
        Texture *texture = textureManager->loadShadowTexture(1024, 1024);

        uint32_t fbo;
        this->graphicsWrapper->generateFrameBuffer(fbo, texture->getId());
        item->shadowData = UPTR<ShadowData>(new ShadowData{ fbo, texture->getId(), texture->getUnit() });

        glm::vec3 position = glm::vec3(0.0f) - (item->getDirection() *  10.0f);

        glm::mat4 lightView = glm::lookAt
        (
            position,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        item->lightSpaceMatrix = lightProjection * lightView;
    }
}

void ShadowRenderer::setupPointLightShader(TextureManager *textureManager)
{
    this->pointLightDepthShader = this->shaderManager->loadPointLightDepthShader();

    for (PointLightComponent *item : this->lightManager->pointLights)
    {
        Texture *texture = textureManager->loadCubemapTexture(1024, 1024);

        uint32_t fbo;
        this->graphicsWrapper->generateFrameBuffer(fbo, texture->getId(), true);
        item->shadowData = UPTR<ShadowData>(new ShadowData{ fbo, texture->getId(), texture->getUnit() });
    }

    this->shaderManager->setupUniformLocation(this->pointLightDepthShader, ShaderVariables::MODEL_MATRIX);
    this->shaderManager->setupUniformLocation(this->pointLightDepthShader, ShaderVariables::FAR_PLANE);
    this->shaderManager->setupUniformLocation(this->pointLightDepthShader, ShaderVariables::LIGHT_POSITION);

    char variable[32];
    for (unsigned int i = 0; i < 6; ++i)
    {
        sprintf_s(variable, POINT_SHADOW_MATRICES_FORMAT, i);
        this->shaderManager->setupUniformLocation(this->pointLightDepthShader, variable);
    }
}

void ShadowRenderer::addItem(MeshComponent *item)
{
    this->items.push_back(item);
}

void ShadowRenderer::render()
{
    this->graphicsWrapper->clearBuffer();

    this->graphicsWrapper->setViewport(1024, 1024);

    if (this->lightManager->pointLights.size() > 0)
        this->renderPointLightShadows();

    if (this->lightManager->directionalLights.size() > 0)
        this->renderDirectionalLightShadows();

    this->graphicsWrapper->unbindFrameBuffer();
}

void ShadowRenderer::renderDirectionalLightShadows()
{
    this->shaderManager->enableShader(this->directionalLightDepthShader);

    for (DirectionalLightComponent *light : this->lightManager->directionalLights)
    {
        this->graphicsWrapper->bindFrameBuffer(light->shadowData->fbo);
        this->graphicsWrapper->clearDepthBuffer();
        this->shaderManager->setMat4(this->directionalLightDepthShader, ShaderVariables::LIGHT_SPACE_MATRIX, &light->lightSpaceMatrix[0][0]);

        for (MeshComponent *item : this->items)
        {
            TransformComponent *transform = item->getTransform();
            glm::mat4 modelMatrix = transform->getMatrix();
            this->shaderManager->setMat4(this->directionalLightDepthShader, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

            this->graphicsWrapper->bindVAO(item->vao, item->vbo);

            this->graphicsWrapper->enableVertexPositions();
            this->graphicsWrapper->drawElement(item->meshData->indices.size());
            this->graphicsWrapper->disableVertexPositions();
        }
    }
}

void ShadowRenderer::renderPointLightShadows()
{
    this->shaderManager->enableShader(this->pointLightDepthShader);

    char variable[32];
    for (PointLightComponent *light : this->lightManager->pointLights)
    {
        this->graphicsWrapper->bindFrameBuffer(light->shadowData->fbo);
        this->graphicsWrapper->clearDepthBuffer();

        glm::vec3 lightPosition = light->getPosition();
        this->updateShadowMatrices(lightPosition, light->getRange());

        for (unsigned int i = 0; i < 6; ++i)
        {
            sprintf_s(variable, POINT_SHADOW_MATRICES_FORMAT, i);
            this->shaderManager->setMat4(this->pointLightDepthShader, variable, &this->shadowMatrices[i][0][0]);
        }

        this->shaderManager->setFloat(this->pointLightDepthShader, ShaderVariables::FAR_PLANE, light->getRange());
        this->shaderManager->setVec3(this->pointLightDepthShader, ShaderVariables::LIGHT_POSITION, &lightPosition[0]);

        for (MeshComponent *item : this->items)
        {
            TransformComponent *transform = item->getTransform();
            glm::mat4 modelMatrix = transform->getMatrix();
            this->shaderManager->setMat4(this->pointLightDepthShader, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

            this->graphicsWrapper->bindVAO(item->vao, item->vbo);

            this->graphicsWrapper->enableVertexPositions();
            this->graphicsWrapper->drawElement(item->meshData->indices.size());
            this->graphicsWrapper->disableVertexPositions();
        }
    }
}

void ShadowRenderer::removeDestroyedEntities()
{
    std::experimental::erase_if
    (
        this->items,
        [](MeshComponent *item) { return !item->getEntity()->isAlive(); }
    );
}

void ShadowRenderer::updateShadowMatrices(const glm::vec3 &lightPosition, float range)
{
    float aspect = 1024.0f / 1024.0f;
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
