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
    Texture *texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadShadowTexture(1024, 1024);
    this->lightManager->depthMap = texture->getId();

    this->graphicsWrapper->generateFrameBuffer(depthMapFBO, this->lightManager->depthMap);

    this->shaderManager->setupUniformLocation(this->depthShader, ShaderVariables::LIGHT_SPACE_MATRIX);
    this->shaderManager->setupUniformLocation(this->depthShader, ShaderVariables::MODEL_MATRIX);
    glm::vec3 position = glm::vec3(0.0f) - (this->lightManager->directionalLights[0]->getDirection() *  10.0f);

    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f);
    glm::mat4 lightView = glm::lookAt
    (
        position,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    this->lightManager->lightSpaceMatrix = lightProjection * lightView;
}

void ShadowRenderer::addItem(MeshComponent *item)
{
    this->items.push_back(item);
}

void ShadowRenderer::render()
{
    this->graphicsWrapper->clearBuffer();

    this->shaderManager->enableShader(this->depthShader);
    this->shaderManager->setMat4(this->depthShader, ShaderVariables::LIGHT_SPACE_MATRIX, &this->lightManager->lightSpaceMatrix[0][0]);

    this->graphicsWrapper->setViewport(1024, 1024);
    this->graphicsWrapper->bindFrameBuffer(depthMapFBO);
    this->graphicsWrapper->enableFrontCullFace();

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

    this->graphicsWrapper->disableFrontCullFace();
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
