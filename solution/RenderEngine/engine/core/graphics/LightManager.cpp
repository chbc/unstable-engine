#include "LightManager.h"

#include <engine/entities/Entity.h>
#include <experimental/vector>
#include "ShaderManager.h"
#include <engine/core/wrappers/graphics/OpenGLAPI.h>
#include <engine/core/singletonsManager/SingletonsManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <engine/entities/components/renderables/meshes/MeshComponent.h>
#include <engine/core/multimedia/textures/TextureManager.h>

namespace sre
{

LightManager::LightManager()
{
    this->ambientLightColor = glm::vec3(0.1f, 0.1f, 0.1f);
}

void LightManager::init()
{
    SingletonsManager *singletonsManager = SingletonsManager::getInstance();
    this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
    this->shaderManager = singletonsManager->get<ShaderManager>();
    depthShader = this->shaderManager->loadDepthShader();
}

void LightManager::onSceneLoaded()
{
    Texture *texture = SingletonsManager::getInstance()->resolve<TextureManager>()->loadShadowTexture(1024, 1024);
    this->depthMap = texture->getId();

    graphicsWrapper->generateFrameBuffer(depthMapFBO, depthMap);

    this->shaderManager->setupUniformLocation(this->depthShader, ShaderVariables::SOURCE_SPACE_MATRIX);
    this->shaderManager->setupUniformLocation(this->depthShader, ShaderVariables::MODEL_MATRIX);
}

void LightManager::generateDepthMap()
{
    this->graphicsWrapper->clearBuffer();

    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
    glm::mat4 lightView = glm::lookAt(glm::vec3(0.0f, 4.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    this->shaderManager->enableShader(this->depthShader);
    this->shaderManager->setMat4(this->depthShader, ShaderVariables::SOURCE_SPACE_MATRIX, &lightSpaceMatrix[0][0]);

    graphicsWrapper->setViewport(1024, 1024);
    OpenGLAPI::bindFrameBuffer(depthMapFBO);

    OpenGLAPI::enableFrontCullFace();
    for (MeshComponent *item : this->meshes)
    {
        TransformComponent *transform = item->getTransform();
        glm::mat4 modelMatrix = transform->getMatrix();
        this->shaderManager->setMat4(this->depthShader, ShaderVariables::MODEL_MATRIX, &modelMatrix[0][0]);

        this->graphicsWrapper->bindVAO(item->vao, item->vbo);

        this->graphicsWrapper->enableVertexPositions();
        this->graphicsWrapper->drawElement(item->meshData->indices.size());
        this->graphicsWrapper->disableVertexPositions();
    }
    OpenGLAPI::disableFrontCullFace();

    graphicsWrapper->unbindFrameBuffer();
}

void LightManager::addShadowCaster(MeshComponent *mesh)
{
    this->meshes.push_back(mesh);
}

void LightManager::setAmbientLightColor(const glm::vec3 &ambientLightColor)
{
    this->ambientLightColor = ambientLightColor;
}

DirectionalLightComponent *LightManager::addDirectionalLight(Entity *entity)
{
    DirectionalLightComponent *newLight = entity->addComponent<DirectionalLightComponent>();
    this->directionalLights.push_back(newLight);

    return newLight;
}

PointLightComponent *LightManager::addPointLight(Entity *entity)
{
    PointLightComponent *newLight = entity->addComponent<PointLightComponent>();
    this->pointLights.push_back(newLight);

    return newLight;
}

void LightManager::removeDestroyedEntities()
{
    std::experimental::erase_if
    (
        this->directionalLights, 
        [](DirectionalLightComponent *item) { return !item->getEntity()->isAlive(); }
    );

    std::experimental::erase_if
    (
        this->pointLights,
        [](PointLightComponent *item) { return !item->getEntity()->isAlive(); }
    );

    std::experimental::erase_if
    (
        this->meshes,
        [](MeshComponent *item) { return !item->getEntity()->isAlive(); }
    );
}

} // namespace
