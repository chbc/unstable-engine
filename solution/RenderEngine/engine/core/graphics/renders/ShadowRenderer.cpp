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

ShadowRenderer::ShadowRenderer()
{
    SingletonsManager *singletonsManager = SingletonsManager::getInstance();
    this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
    this->shaderManager = singletonsManager->get<ShaderManager>();
}

void ShadowRenderer::onSceneLoaded()
{
    depthShader = this->shaderManager->loadDepthShader();

    this->lightManager = SingletonsManager::getInstance()->get<LightManager>();
    for (PointLightComponent *pointLight : this->lightManager->pointLights)
    {
        Texture *texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadCubemapTexture(1024, 1024);
        pointLight->depthCubemap = texture->getId();
        this->graphicsWrapper->generateFrameBuffer(pointLight->fbo, pointLight->depthCubemap, true);
    }

    this->shaderManager->setupUniformLocation(this->depthShader, ShaderVariables::MODEL_MATRIX);
    this->shaderManager->setupUniformLocation(this->depthShader, ShaderVariables::FAR_PLANE);
    this->shaderManager->setupUniformLocation(this->depthShader, ShaderVariables::LIGHT_POSITION);
    
    char variable[32];
    for (unsigned int i = 0; i < 6; ++i)
    {
        sprintf_s(variable, SHADOW_MATRICES_FORMAT, i);
        this->shaderManager->setupUniformLocation(this->depthShader, variable);
    }

    float aspect = 1024.0f / 1024.0f;
    float near = 0.1f;
    this->farPlane = 50.0f;
    this->projection = glm::perspective(glm::radians(90.0f), aspect, near, this->farPlane);
}

void ShadowRenderer::addItem(MeshComponent *item)
{
    this->items.push_back(item);
}

void ShadowRenderer::render()
{
    this->graphicsWrapper->clearBuffer();

    this->graphicsWrapper->setViewport(1024, 1024);

    this->shaderManager->enableShader(this->depthShader);
    // ### this->graphicsWrapper->enableFrontCullFace();

    char variable[32];
    for (PointLightComponent *pointLight : this->lightManager->pointLights)
    {
        this->graphicsWrapper->bindFrameBuffer(pointLight->fbo);
        this->graphicsWrapper->clearDepthBuffer();

        glm::vec3 lightPosition = pointLight->getPosition();
        this->updateShadowMatrices(lightPosition);

        for (unsigned int i = 0; i < 6; ++i)
        {
            sprintf_s(variable, SHADOW_MATRICES_FORMAT, i);
            this->shaderManager->setMat4(this->depthShader, variable, &this->shadowMatrices[i][0][0]);
        }

        this->shaderManager->setFloat(this->depthShader, ShaderVariables::FAR_PLANE, this->farPlane);
        this->shaderManager->setVec3(this->depthShader, ShaderVariables::LIGHT_POSITION, &lightPosition[0]);

        for (MeshComponent *item : this->items)
        {
            TransformComponent *transform = item->getTransform();
            glm::mat4 modelMatrix = transform->getMatrix();
            this->shaderManager->setMat4(this->depthShader, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

            this->graphicsWrapper->bindVAO(item->vao, item->vbo);

            this->graphicsWrapper->enableVertexPositions();
            this->graphicsWrapper->drawElement(item->meshData->indices.size());
            this->graphicsWrapper->disableVertexPositions();
        }
    }

    // ### this->graphicsWrapper->disableFrontCullFace();
    this->graphicsWrapper->unbindFrameBuffer();
}

void ShadowRenderer::removeDestroyedEntities()
{
    std::experimental::erase_if
    (
        this->items,
        [](MeshComponent *item) { return !item->getEntity()->isAlive(); }
    );
}

void ShadowRenderer::updateShadowMatrices(const glm::vec3 &lightPosition)
{
    this->shadowMatrices[0] = glm::mat4(this->projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    this->shadowMatrices[1] = glm::mat4(this->projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    this->shadowMatrices[2] = glm::mat4(this->projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    this->shadowMatrices[3] = glm::mat4(this->projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
    this->shadowMatrices[4] = glm::mat4(this->projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    this->shadowMatrices[5] = glm::mat4(this->projection * glm::lookAt(lightPosition, lightPosition + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
}

} // namespace
