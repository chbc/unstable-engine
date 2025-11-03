#include "ShadowRenderer.h"
#include "MeshComponent.h"
#include "SingletonsManager.h"
#include "TextureCreator.h"
#include "LightManager.h"
#include "ShaderManager.h"
#include "AGraphicsWrapper.h"
#include "Entity.h"
#include "StringUtils.h"
#include "CollectionsUtils.h"

namespace sre
{

void ShadowRenderer::init()
{
    SingletonsManager *singletonsManager = SingletonsManager::getInstance();
    this->graphicsWrapper = singletonsManager->get<AGraphicsWrapper>();
    this->shaderManager = singletonsManager->get<ShaderManager>();
    this->lightManager = singletonsManager->get<LightManager>();
    textureCreator = singletonsManager->get<TextureCreator>();

    if (this->lightManager->directionalLights.size() > 0)
        this->setupDirectionalLightShader();

    if (this->lightManager->pointLights.size() > 0)
        this->setupPointLightShader();
}

void ShadowRenderer::setupDirectionalLightShader()
{
    this->directionalLightDepthProgram = this->shaderManager->loadDirectionalLightDepthShader();

    this->shaderManager->setupUniformLocation(this->directionalLightDepthProgram, ShaderVariables::LIGHT_SPACE_MATRIX);
    this->shaderManager->setupUniformLocation(this->directionalLightDepthProgram, ShaderVariables::MODEL_MATRIX);

    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f);

    for (DirectionalLightComponent *item : this->lightManager->directionalLights)
    {
        Texture *texture = textureCreator->createShadowTexture(1024, 1024);

        uint32_t fbo = this->graphicsWrapper->generateDepthFrameBuffer(texture->getId());
        item->shadowData = UPTR<ShadowData>(new ShadowData{ fbo, texture->getId(), texture->getUnit() });

        TransformComponent* transform = item->getTransform();
        glm::vec3 position = glm::vec3(0.0f) - (transform->getForward() *  10.0f);

        glm::mat4 lightView = glm::lookAt
        (
            position,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        item->lightSpaceMatrix = lightProjection * lightView;
    }
}

void ShadowRenderer::setupPointLightShader()
{
    this->pointLightDepthProgram = this->shaderManager->loadPointLightDepthShader();

    for (PointLightComponent *item : this->lightManager->pointLights)
    {
        Texture *texture = textureCreator->createCubemapTexture(1024, 1024);

        uint32_t fbo = this->graphicsWrapper->generateDepthFrameBuffer(texture->getId(), true);
        item->shadowData = UPTR<ShadowData>(new ShadowData{ fbo, texture->getId(), texture->getUnit() });
    }

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

void ShadowRenderer::addItem(MeshComponent *item)
{
    this->items.push_back(item);
}

void ShadowRenderer::render()
{
    this->graphicsWrapper->clearColorAndDepthBuffer();

    this->graphicsWrapper->setViewport(1024, 1024);

    if (this->lightManager->pointLights.size() > 0)
        this->renderPointLightShadows();

    if (this->lightManager->directionalLights.size() > 0)
        this->renderDirectionalLightShadows();

    this->graphicsWrapper->unbindFrameBuffer();
}

void ShadowRenderer::renderDirectionalLightShadows()
{
    this->shaderManager->enableShader(this->directionalLightDepthProgram);

    for (DirectionalLightComponent *light : this->lightManager->directionalLights)
    {
        this->graphicsWrapper->bindFrameBuffer(light->shadowData->fbo);
        this->graphicsWrapper->clearDepthBuffer();
        this->shaderManager->setMat4(this->directionalLightDepthProgram, ShaderVariables::LIGHT_SPACE_MATRIX, &light->lightSpaceMatrix[0][0]);

        for (MeshComponent *item : this->items)
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

        for (MeshComponent *item : this->items)
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

void ShadowRenderer::removeDestroyedEntities()
{
    CollectionsUtils::removeComponentIfEntityIsDestroyed(this->items);
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
