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
    Texture *texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadCubemapTexture(1024, 1024);
    this->lightManager->depthCubemap = texture->getId();

    this->graphicsWrapper->generateFrameBuffer(depthMapFBO, this->lightManager->depthCubemap, true);

    this->shaderManager->setupUniformLocation(this->depthShader, ShaderVariables::MODEL_MATRIX);
    this->shaderManager->setupUniformLocation(this->depthShader, ShaderVariables::FAR_PLANE);
    this->shaderManager->setupUniformLocation(this->depthShader, ShaderVariables::LIGHT_POSITION);
    
    char variable[32];
    for (unsigned int i = 0; i < 6; ++i)
    {
        sprintf_s(variable, SHADOW_MATRICES_FORMAT, i);
        this->shaderManager->setupUniformLocation(this->depthShader, variable);
    }

    glm::vec3 lightPos = this->lightManager->pointLights[0]->getPosition();
    float aspect = 1024.0f / 1024.0f;
    float near = 1.0f;
    this->farPlane = 25.0f;
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), aspect, near, this->farPlane);

    this->shadowMatrices.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0, 0.0, 0.0),  glm::vec3(0.0, -1.0, 0.0)));
    this->shadowMatrices.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    this->shadowMatrices.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 1.0, 0.0),  glm::vec3(0.0, 0.0, 1.0)));
    this->shadowMatrices.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
    this->shadowMatrices.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, 1.0),  glm::vec3(0.0, -1.0, 0.0)));
    this->shadowMatrices.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
}

void ShadowRenderer::addItem(MeshComponent *item)
{
    this->items.push_back(item);
}

void ShadowRenderer::render()
{
    this->graphicsWrapper->clearBuffer();

    this->graphicsWrapper->setViewport(1024, 1024);
    this->graphicsWrapper->bindFrameBuffer(depthMapFBO);
    this->graphicsWrapper->clearDepthBuffer();

    this->shaderManager->enableShader(this->depthShader);
    // ### this->graphicsWrapper->enableFrontCullFace();

    char variable[32];
    for (unsigned int i = 0; i < 6; ++i)
    {
        sprintf_s(variable, SHADOW_MATRICES_FORMAT, i);
        this->shaderManager->setMat4(this->depthShader, variable, &this->shadowMatrices[i][0][0]);
    }
    
    glm::vec3 lightPosition = this->lightManager->pointLights[0]->getPosition();
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

} // namespace
